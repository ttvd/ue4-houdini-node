#include "HoudiniNodeGeneratorStaticMesh.h"
#include "HoudiniNodeClass.h"
#include "HoudiniNodeAttributeCast.h"
#include "HoudiniNodeAttributePrimitive.h"
#include "HoudiniNodeModule.h"
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


#if WITH_EDITOR

static
bool
IsInvalidRawMesh(FRawMesh& RawMesh)
{
    int32 NumDenegerateTris = 0;
    int32 NumWedges = RawMesh.WedgeIndices.Num();
    int32 NumFaces = NumWedges / 3;

    for(int32 WedgeIdx = 0; WedgeIdx < NumWedges; WedgeIdx += 3)
    {
        const FVector& Vertex0 = RawMesh.VertexPositions[RawMesh.WedgeIndices[WedgeIdx + 0]];
        const FVector& Vertex1 = RawMesh.VertexPositions[RawMesh.WedgeIndices[WedgeIdx + 1]];
        const FVector& Vertex2 = RawMesh.VertexPositions[RawMesh.WedgeIndices[WedgeIdx + 2]];

        if(Vertex0.Equals(Vertex1, THRESH_POINTS_ARE_SAME) || Vertex0.Equals(Vertex2, THRESH_POINTS_ARE_SAME) ||
            Vertex1.Equals(Vertex2, THRESH_POINTS_ARE_SAME))
        {
            NumDenegerateTris++;
        }
    }

    return NumDenegerateTris > 0;
}

#endif


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

    const FHoudiniNodeDetail& Detail = NodeClass->GetDetail();

    TMap<FString, TMap<int32, TArray<GA_Primitive*> > > GeneratorParts;
    if(!Detail.GetPartPrims(GeneratorParts))
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
UHoudiniNodeGeneratorStaticMesh::CreateStaticMeshActor(UHoudiniNodeClass* NodeClass,
    const TArray<GA_Primitive*>& Primitives) const
{
    if(!NodeClass || !Primitives.Num())
    {
        return nullptr;
    }

    UWorld* World = GetCurrentWorld(NodeClass);

    const FHoudiniNodeDetail& Detail = NodeClass->GetDetail();
    if(!Detail.IsValid())
    {
        return nullptr;
    }

    FTransform StaticMeshActorTransform = FTransform::Identity;

    // Extract transforms specified on the primitives and pick the first one.
    {
        TArray<FTransform> PrimitiveTransforms;
        if(Detail.GetPrimitivePartTransforms(Primitives, PrimitiveTransforms))
        {
            StaticMeshActorTransform = PrimitiveTransforms[0];
        }
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

    AssignStaticMeshComponentCollisionProfile(NodeClass, StaticMeshComponent, StaticMesh, Primitives);

    StaticMeshComponent->SetMobility(EComponentMobility::Movable);
    StaticMeshComponent->SetStaticMesh(StaticMesh);
    StaticMeshComponent->SetMobility(EComponentMobility::Static);

    return StaticMeshActor;
}


UStaticMesh*
UHoudiniNodeGeneratorStaticMesh::CreateStaticMesh(UHoudiniNodeClass* NodeClass, UObject* Outer,
    const TArray<GA_Primitive*>& Primitives) const
{
    if(!NodeClass)
    {
        return nullptr;
    }

    const FHoudiniNodeDetail& Detail = NodeClass->GetDetail();
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

    if(!Detail.GetAllPointPositions(RawMesh.VertexPositions))
    {
        return nullptr;
    }

    const int32 FaceCount = Primitives.Num();
    const int32 VertexCount = FaceCount * 3;

    RawMesh.FaceSmoothingMasks.SetNumZeroed(FaceCount);
    RawMesh.FaceMaterialIndices.SetNumZeroed(FaceCount);

    if(!Detail.GetPrimitivePoints(Primitives, RawMesh.WedgeIndices))
    {
        return nullptr;
    }

    if(IsInvalidRawMesh(RawMesh))
    {
        return nullptr;
    }

    TArray<FStaticMaterial> StaticMeshMaterials;

    if(!GetFaceMaterials(NodeClass, Primitives, RawMesh.FaceMaterialIndices, StaticMeshMaterials))
    {
        return nullptr;
    }

    GetVertexNormals(NodeClass, Primitives, VertexCount, RawMesh.WedgeTangentZ);
    GetVertexColors(NodeClass, Primitives, VertexCount, RawMesh.WedgeColors);

    TArray<int32> UnusedUVChannels;

    for(int32 Idx = 0; Idx < MAX_MESH_TEXTURE_COORDS; ++Idx)
    {
        TArray<FVector2D>& UVs = RawMesh.WedgeTexCoords[Idx];
        if(!GetVertexUVs(NodeClass, Primitives, VertexCount, Idx, UVs))
        {
            UnusedUVChannels.Add(Idx);
        }
    }

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

    if(SrcModel->BuildSettings.bGenerateLightmapUVs)
    {
        // Use first unused UV channel for generating light maps uvs.
        if(UnusedUVChannels.Num() > 0)
        {
            StaticMesh->LightMapCoordinateIndex = UnusedUVChannels[0];
        }
    }
    else
    {
        // We have no available uv channels.
        SrcModel->BuildSettings.bGenerateLightmapUVs = false;
    }

    // Assign mesh materials.
    StaticMesh->StaticMaterials = StaticMeshMaterials;

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

    AssignStaticMeshCollision(NodeClass, StaticMesh, Primitives);

    {
        FHoudiniNodeGeneratorStaticMeshGlobalSilence HoudiniNodeGeneratorStaticMeshGlobalSilence;
        StaticMesh->Build(true);
    }

    StaticMesh->MarkPackageDirty();

#endif

    return StaticMesh;
}


bool
UHoudiniNodeGeneratorStaticMesh::AssignStaticMeshCollision(UHoudiniNodeClass* NodeClass, UStaticMesh* StaticMesh,
    const TArray<GA_Primitive*>& Primitives) const
{
    if(!NodeClass || !StaticMesh)
    {
        return false;
    }

    const FHoudiniNodeDetail& Detail = NodeClass->GetDetail();
    if(!Detail.IsValid())
    {
        return false;
    }

    FHoudiniNodeAttributePrimitive Attribute(Detail, HOUDINI_NODE_ATTRIBUTE_ASSIGN_COLLISION);
    if(Attribute.Exists())
    {
        TArray<FString> Values;
        if(Attribute.Get(Primitives, Values))
        {
            const FString& GenerateCollisionValue = Values[0];

            UBodySetup* BodySetup = StaticMesh->BodySetup;
            if(!BodySetup)
            {
                StaticMesh->CreateBodySetup();
                BodySetup = StaticMesh->BodySetup;
            }

            if(BodySetup)
            {
                BodySetup->CollisionTraceFlag = ECollisionTraceFlag::CTF_UseDefault;

                if(GenerateCollisionValue.Equals(HOUDINI_NODE_ATTRIBUTE_ASSIGN_COLLISION_SIMPLE_AND_COMPLEX,
                    ESearchCase::IgnoreCase))
                {
                    BodySetup->CollisionTraceFlag = ECollisionTraceFlag::CTF_UseSimpleAndComplex;
                }
                else if(GenerateCollisionValue.Equals(HOUDINI_NODE_ATTRIBUTE_ASSIGN_COLLISION_SIMPLE_AS_COMPLEX,
                    ESearchCase::IgnoreCase))
                {
                    BodySetup->CollisionTraceFlag = ECollisionTraceFlag::CTF_UseSimpleAsComplex;
                }
                else if(GenerateCollisionValue.Equals(HOUDINI_NODE_ATTRIBUTE_ASSIGN_COLLISION_COMPLEX_AS_SIMPLE,
                    ESearchCase::IgnoreCase))
                {
                    BodySetup->CollisionTraceFlag = ECollisionTraceFlag::CTF_UseComplexAsSimple;
                }

                BodySetup->bMeshCollideAll = true;

                return true;
            }
        }
    }

    return false;
}


bool
UHoudiniNodeGeneratorStaticMesh::AssignStaticMeshComponentCollisionProfile(UHoudiniNodeClass* NodeClass,
    UStaticMeshComponent* StaticMeshComponent, UStaticMesh* StaticMesh, const TArray<GA_Primitive*>& Primitives) const
{
    if(!NodeClass || !StaticMesh || !StaticMeshComponent)
    {
        return false;
    }

    const FHoudiniNodeDetail& Detail = NodeClass->GetDetail();
    if(!Detail.IsValid())
    {
        return false;
    }

    FHoudiniNodeAttributePrimitive Attribute(Detail, HOUDINI_NODE_ATTRIBUTE_ASSIGN_COLLISION_PROFILE);
    if(Attribute.Exists())
    {
        TArray<FString> Values;
        if(Attribute.Get(Primitives, Values))
        {
            const FString& CollisionProfile = Values[0];

            TArray<TSharedPtr<FName> > ValidCollisionProfiles;
            UCollisionProfile::GetProfileNames(ValidCollisionProfiles);

            for(int32 ValidProfileIdx = 0; ValidProfileIdx < ValidCollisionProfiles.Num(); ++ValidProfileIdx)
            {
                TSharedPtr<FName> ValidProfileName = ValidCollisionProfiles[ValidProfileIdx];
                if(ValidProfileName.IsValid())
                {
                    const FString& ProfileNameString = ValidProfileName.Get()->ToString();
                    if(ProfileNameString.Equals(CollisionProfile, ESearchCase::IgnoreCase))
                    {
                        StaticMeshComponent->SetCollisionProfileName(*ProfileNameString);
                        return true;
                    }
                }
            }
        }
    }

    UBodySetup* BodySetup = StaticMesh->BodySetup;
    if(BodySetup)
    {
        if(BodySetup->CollisionTraceFlag != ECollisionTraceFlag::CTF_UseDefault)
        {
            StaticMeshComponent->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
        }
        else
        {
            StaticMeshComponent->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
        }
    }
    else
    {
        StaticMeshComponent->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
    }

    return true;
}


bool
UHoudiniNodeGeneratorStaticMesh::GetVertexNormals(UHoudiniNodeClass* NodeClass, const TArray<GA_Primitive*>& Primitives,
    uint32 VertexCount, TArray<FVector>& Normals) const
{
    Normals.Empty();

    if(!NodeClass)
    {
        return false;
    }

    const FHoudiniNodeDetail& Detail = NodeClass->GetDetail();
    if(!Detail.IsValid())
    {
        return false;
    }

    FHoudiniNodeAttributeCast Attribute(Detail, HOUDINI_NODE_ATTRIBUTE_NORMAL);
    if(!Attribute.GetAsVertex(Primitives, false, Normals))
    {
        const FVector& DefaultNormal = FVector::UpVector;
        Normals.Init(DefaultNormal, VertexCount);
    }

    PatchVertexWindingOrder(Normals);
    return true;
}


bool
UHoudiniNodeGeneratorStaticMesh::GetVertexColors(UHoudiniNodeClass* NodeClass, const TArray<GA_Primitive*>& Primitives,
    uint32 VertexCount, TArray<FColor>& Colors) const
{
    Colors.Empty();

    if(!NodeClass)
    {
        return false;
    }

    const FHoudiniNodeDetail& Detail = NodeClass->GetDetail();
    if(!Detail.IsValid())
    {
        return false;
    }

    FHoudiniNodeAttributeCast Attribute(Detail, HOUDINI_NODE_ATTRIBUTE_COLOR);
    if(!Attribute.GetAsVertex(Primitives, Colors))
    {
        const FColor& DefaultColor = FColor::White;
        Colors.Init(DefaultColor, VertexCount);
    }

    PatchVertexWindingOrder(Colors);
    return true;
}


bool
UHoudiniNodeGeneratorStaticMesh::GetVertexUVs(UHoudiniNodeClass* NodeClass, const TArray<GA_Primitive*>& Primitives,
    uint32 VertexCount, uint32 Channel, TArray<FVector2D>& UVs) const
{
    UVs.Empty();

    if(!NodeClass)
    {
        return false;
    }

    const FHoudiniNodeDetail& Detail = NodeClass->GetDetail();
    if(!Detail.IsValid())
    {
        return false;
    }

    FString AttributeName = HOUDINI_NODE_ATTRIBUTE_UV;

    if(Channel > 0)
    {
        AttributeName = FString::Printf(TEXT("uv%d"), (Channel + 1));
    }

    FHoudiniNodeAttributeCast Attribute(Detail, AttributeName);

    /*
    if(!Attribute.GetAsVertex(Primitives, UVs))
    {
        const FVector2D& DefaultUV = FVector2D::ZeroVector;
        UVs.Init(DefaultUV, VertexCount);
    }

    return true;
    */

    if(!Attribute.GetAsVertex(Primitives, true, UVs))
    {
        return false;
    }

    PatchVertexWindingOrder(UVs);
    return true;
}


bool
UHoudiniNodeGeneratorStaticMesh::GetFaceMaterials(UHoudiniNodeClass* NodeClass, const TArray<GA_Primitive*>& Primitives,
    TArray<int32>& FaceMaterialIndices, TArray<FStaticMaterial>& Materials) const
{
    FaceMaterialIndices.Empty();
    Materials.Empty();

    if(!NodeClass)
    {
        return false;
    }

    const FHoudiniNodeDetail& Detail = NodeClass->GetDetail();
    if(!Detail.IsValid())
    {
        return false;
    }

    const int32 PrimitiveCount = Primitives.Num();

    UMaterialInterface* DefaultMaterial = GHoudiniNode->GetDefaultMaterial();
    if(!DefaultMaterial)
    {
        return false;
    }

    FHoudiniNodeAttributePrimitive Attribute(Detail, HOUDINI_NODE_ATTRIBUTE_MATERIAL);
    if(Attribute.Exists())
    {
        TMap<UObject*, TArray<GA_Primitive*> > PrimitiveMaterialGroups;

        TArray<UObject*> MaterialAssignments;

        int32 MaterialIndexMax = 0;
        TMap<UMaterialInterface*, int32> MaterialIndices;

        if(Attribute.Get(Primitives, MaterialAssignments))
        {
            for(int32 Idx = 0; Idx < MaterialAssignments.Num(); ++Idx)
            {
                UMaterialInterface* MaterialInterface = Cast<UMaterialInterface>(MaterialAssignments[Idx]);
                if(!MaterialInterface)
                {
                    MaterialInterface = DefaultMaterial;
                }

                int32* FoundAssignment = MaterialIndices.Find(MaterialInterface);
                if(FoundAssignment)
                {
                    int32 MaterialIndex = *FoundAssignment;
                    FaceMaterialIndices.Add(MaterialIndex);
                }
                else
                {
                    MaterialIndices.Add(MaterialInterface, MaterialIndexMax);
                    Materials.Add(FStaticMaterial(MaterialInterface));
                    FaceMaterialIndices.Add(MaterialIndexMax);

                    MaterialIndexMax++;
                }
            }

            return true;
        }
    }

    FaceMaterialIndices.Init(0, PrimitiveCount);
    Materials.Add(FStaticMaterial(DefaultMaterial));

    return true;
}

