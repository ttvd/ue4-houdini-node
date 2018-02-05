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
UHoudiniNodeGeneratorStaticMesh::MatchName(const FString& InGeneratorName) const
{
    if(InGeneratorName.IsEmpty())
    {
        return true;
    }

    return Super::MatchName(InGeneratorName);
}


bool
UHoudiniNodeGeneratorStaticMesh::Generate(UHoudiniNodeClass* NodeClass, TArray<AActor*>& GeneratedActors)
{
    if(!Super::Generate(NodeClass, GeneratedActors))
    {
        return false;
    }

    TSharedPtr<FHoudiniNodeDetail> Detail = NodeClass->GetDetail();

    TMap<FString, TMap<int32, TArray<GA_Primitive*> > > GeneratorParts;
    if(!Detail->GetPartPrims(GeneratorParts))
    {
        return false;
    }

    for(TMap<FString, TMap<int32, TArray<GA_Primitive*> > >::TIterator Iter(GeneratorParts); Iter; ++Iter)
    {
        const FString& GeneratorAttribName = Iter.Key();
        const TMap<int32, TArray<GA_Primitive*> >& Parts = Iter.Value();

        if(!MatchName(GeneratorAttribName) || !Parts.Num())
        {
            continue;
        }

        for(TMap<int32, TArray<GA_Primitive*> >::TConstIterator IterParts(Parts); IterParts; ++IterParts)
        {
            const int32 Part = IterParts.Key();
            const TArray<GA_Primitive*>& Primitives = IterParts.Value();

            if(!Primitives.Num())
            {
                continue;
            }

            AStaticMeshActor* Actor = CreateStaticMeshActor(NodeClass, Primitives);
            if(Actor)
            {
                GeneratedActors.Add(Actor);
            }
        }
    }

    return GeneratedActors.Num() > 0;
}


AStaticMeshActor*
UHoudiniNodeGeneratorStaticMesh::CreateStaticMeshActor(UHoudiniNodeClass* NodeClass, const TArray<GA_Primitive*>& Primitives) const
{
    if(!NodeClass || !Primitives.Num())
    {
        return nullptr;
    }

    UWorld* World = GetCurrentWorld(NodeClass);

    FTransform StaticMeshActorTransform = FTransform::Identity;
    {
    
    }

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
        return nullptr;
    }

    UStaticMeshComponent* StaticMeshComponent = StaticMeshActor->GetStaticMeshComponent();
    if(!StaticMeshComponent)
    {
        StaticMeshActor->ConditionalBeginDestroy();
        return nullptr;
    }

    UStaticMesh* StaticMesh = CreateStaticMesh(NodeClass, StaticMeshActor, Primitives);
    if(!StaticMesh)
    {
        StaticMeshActor->ConditionalBeginDestroy();
        return nullptr;
    }

    StaticMeshComponent->SetMobility(EComponentMobility::Movable);
    StaticMeshComponent->SetStaticMesh(StaticMesh);
    StaticMeshComponent->SetMobility(EComponentMobility::Static);

    return StaticMeshActor;
}


UStaticMesh*
UHoudiniNodeGeneratorStaticMesh::CreateStaticMesh(UHoudiniNodeClass* NodeClass, UObject* Outer, const TArray<GA_Primitive*>& Primitives) const
{
    if(!NodeClass)
    {
        return nullptr;
    }

    TSharedPtr<FHoudiniNodeDetail> Detail = NodeClass->GetDetail();
    if(!Detail.IsValid())
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

    if(!Detail->GetPrimitivePointPositions(Primitives, RawMesh.VertexPositions))
    {
        return nullptr;
    }

    const int32 FaceCount = Primitives.Num();
    const int32 VertexCount = FaceCount * 3;

    RawMesh.FaceSmoothingMasks.SetNumZeroed(FaceCount);
    RawMesh.FaceMaterialIndices.SetNumZeroed(FaceCount);

    if(!Detail->GetPrimitivePoints(Primitives, RawMesh.WedgeIndices))
    {
        return nullptr;
    }



    /*
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
    */

#endif

    return StaticMesh;
}

