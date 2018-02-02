#include "HoudiniNodeGeneratorStaticMesh.h"
#include "HoudiniNodePrivatePCH.h"


UHoudiniNodeGeneratorStaticMesh::UHoudiniNodeGeneratorStaticMesh(const FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer)
{
    SupportedClasses.Add(AStaticMeshActor::StaticClass());
}


bool
UHoudiniNodeGeneratorStaticMesh::Generate(GU_Detail* Detail, TArray<AActor*>& GeneratedActors)
{
    if(!Super::Generate(Detail, GeneratedActors))
    {
        return false;
    }



    return true;
}

