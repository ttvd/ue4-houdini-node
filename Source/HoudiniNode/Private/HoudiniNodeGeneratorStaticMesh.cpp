#include "HoudiniNodeGeneratorStaticMesh.h"
#include "HoudiniNodeClass.h"
#include "HoudiniNodePrivatePCH.h"


struct FHoudiniNodeGeneratorStaticMeshGlobalSilence
{
    FHoudiniNodeGeneratorStaticMeshGlobalSilence(bool bInQuiet = true) :
        bQuiet(bInQuiet)
    {
        if(bQuiet)
        {
            bGlobalSilent = GIsSilent;
            GIsSilent = true;
        }
    }

    ~FHoudiniNodeGeneratorStaticMeshGlobalSilence()
    {
        if(bQuiet)
        {
            GIsSilent = bGlobalSilent;
        }
    }

    bool bGlobalSilent;
    bool bQuiet;
};


UHoudiniNodeGeneratorStaticMesh::UHoudiniNodeGeneratorStaticMesh(const FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer)
{
    GeneratorName = TEXT("StaticMeshActor");
    SupportedClasses.Add(AStaticMeshActor::StaticClass());
}


bool
UHoudiniNodeGeneratorStaticMesh::Generate(UHoudiniNodeClass* NodeClass, TArray<AActor*>& GeneratedActors)
{
    if(!Super::Generate(NodeClass, GeneratedActors))
    {
        return false;
    }

    UWorld* World = GetCurrentWorld(NodeClass);

    FTransform StaticMeshActorTransform = FTransform::Identity;

    FActorSpawnParameters SpawnInfo;

    {
        SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        SpawnInfo.bAllowDuringConstructionScript = true;
        SpawnInfo.ObjectFlags = RF_Public | RF_Transactional;
    }

    AStaticMeshActor* StaticMeshActor = World->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(),
        StaticMeshActorTransform, SpawnInfo);

    if(!StaticMeshActor)
    {
        return false;
    }

    UStaticMeshComponent* StaticMeshComponent = StaticMeshActor->GetStaticMeshComponent();
    if(!StaticMeshComponent)
    {
        StaticMeshActor->ConditionalBeginDestroy();
        return false;
    }

    UStaticMesh* StaticMesh = CreateStaticMesh(NodeClass, StaticMeshActor);
    if(!StaticMesh)
    {
        StaticMeshActor->ConditionalBeginDestroy();
        return false;
    }

    StaticMeshComponent->SetMobility(EComponentMobility::Movable);
    StaticMeshComponent->SetStaticMesh(StaticMesh);
    StaticMeshComponent->SetMobility(EComponentMobility::Static);

    GeneratedActors.Add(StaticMeshActor);
    return GeneratedActors.Num() > 0;
}


UStaticMesh*
UHoudiniNodeGeneratorStaticMesh::CreateStaticMesh(UHoudiniNodeClass* NodeClass, UObject* Outer) const
{
    if(!NodeClass)
    {
        return nullptr;
    }

    UStaticMesh* StaticMesh = nullptr;

    if(!Outer)
    {
        Outer = NodeClass->GetHoudiniNodeActor();
    }

#if WITH_EDITOR

    ITargetPlatform* CurrentPlatform = GetTargetPlatformManagerRef().GetRunningTargetPlatform();
    if(!CurrentPlatform)
    {
        return nullptr;
    }

    FRawMesh RawMesh;

    if(!NodeClass->GetAllPointPositions(RawMesh.VertexPositions))
    {
        return nullptr;
    }

    TArray<GA_Primitive*> Primitives;
    if(!NodeClass->GetAllPrimitives(Primitives))
    {
        return nullptr;
    }

    const int32 FaceCount = Primitives.Num();
    const int32 VertexCount = FaceCount * 3;

    RawMesh.FaceSmoothingMasks.SetNumZeroed(FaceCount);
    RawMesh.FaceMaterialIndices.SetNumZeroed(FaceCount);

    RawMesh.WedgeIndices.SetNumUninitialized(VertexCount);

    for(int32 Idx = 0; Idx < FaceCount; ++Idx)
    {
        GA_Primitive* Prim = Primitives[Idx];

        GA_Offset PointOffset0 = Prim->getPointOffset(0);
        GA_Offset PointOffset1 = Prim->getPointOffset(1);
        GA_Offset PointOffset2 = Prim->getPointOffset(2);

        Swap(PointOffset1, PointOffset2);

        RawMesh.WedgeIndices[Idx * 3 + 0] = PointOffset0;
        RawMesh.WedgeIndices[Idx * 3 + 1] = PointOffset1;
        RawMesh.WedgeIndices[Idx * 3 + 2] = PointOffset2;
    }

    RawMesh.WedgeTangentZ.SetNumZeroed(VertexCount);
    RawMesh.WedgeColors.SetNumZeroed(VertexCount);
    RawMesh.WedgeTexCoords[0].SetNumZeroed(VertexCount);

    const FString StaticMeshName = TEXT("HoudiniNodeStaticMesh");
    StaticMesh = NewObject<UStaticMesh>(Outer, FName(*StaticMeshName), RF_Public | RF_Transactional);

    if(!StaticMesh)
    {
        return nullptr;
    }

    FAssetRegistryModule::AssetCreated(StaticMesh);

    if(!StaticMesh->SourceModels.Num())
    {
        new(StaticMesh->SourceModels) FStaticMeshSourceModel();
    }

    FStaticMeshSourceModel* SrcModel = &StaticMesh->SourceModels[0];
    //SrcModel->BuildSettings = MeshBuildSettings;

    {
        SrcModel->BuildSettings.bUseMikkTSpace = false;
        SrcModel->BuildSettings.bRecomputeNormals = false;
        SrcModel->BuildSettings.bRecomputeTangents = false;
        SrcModel->BuildSettings.bGenerateLightmapUVs = false;
    }

    StaticMesh->LightMapCoordinateIndex = 0;

    UMaterialInterface* DefaultMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("Material'/Engine/EngineMaterials/DefaultMaterial.DefaultMaterial'"), nullptr, LOAD_None, nullptr);
    StaticMesh->StaticMaterials.Empty();
    StaticMesh->StaticMaterials.Add(FStaticMaterial(DefaultMaterial));

    // Store the new raw mesh.
    SrcModel->RawMeshBulkData->SaveRawMesh(RawMesh);

    // Get number of LODs.
    const FStaticMeshLODGroup& LODGroup = CurrentPlatform->GetStaticMeshLODSettings().GetLODGroup(NAME_None);
    int32 NumLODs = LODGroup.GetDefaultNumLODs();

    while(StaticMesh->SourceModels.Num() < NumLODs)
    {
        new(StaticMesh->SourceModels) FStaticMeshSourceModel();
    }

    for(int32 ModelLODIndex = 0; ModelLODIndex < NumLODs; ++ModelLODIndex)
    {
        StaticMesh->SourceModels[ModelLODIndex].ReductionSettings = LODGroup.GetDefaultSettings(ModelLODIndex);

        for(int32 MaterialIndex = 0; MaterialIndex < StaticMesh->StaticMaterials.Num(); ++MaterialIndex)
        {
            FMeshSectionInfo Info = StaticMesh->SectionInfoMap.Get(ModelLODIndex, MaterialIndex);
            Info.MaterialIndex = MaterialIndex;
            Info.bEnableCollision = true;
            Info.bCastShadow = true;
            StaticMesh->SectionInfoMap.Set(ModelLODIndex, MaterialIndex, Info);
        }
    }

    {
        FHoudiniNodeGeneratorStaticMeshGlobalSilence HoudiniNodeGeneratorStaticMeshGlobalSilence;
        StaticMesh->Build(true);
    }

    StaticMesh->MarkPackageDirty();

#endif

    return StaticMesh;
}

