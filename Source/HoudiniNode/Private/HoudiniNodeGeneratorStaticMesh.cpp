#include "HoudiniNodeGeneratorStaticMesh.h"
#include "HoudiniNodeClass.h"
#include "HoudiniNodePrivatePCH.h"


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

    TArray<GA_Primitive*> Primitives;
    if(!NodeClass->GetAllPrimitives(Primitives))
    {
        return false;
    }

#if WITH_EDITOR

    FRawMesh RawMesh;

    //GA_Primitive* prim;
    //prim->getPointOffset

#endif

    return GeneratedActors.Num() > 0;
}

