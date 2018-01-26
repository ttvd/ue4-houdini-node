#include "HoudiniNodePrivatePCH.h"
#include "HoudiniNodeComponent.h"


UHoudiniNodeComponent::UHoudiniNodeComponent(const FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer)
{

}


UHoudiniNodeComponent::~UHoudiniNodeComponent()
{

}


void
UHoudiniNodeComponent::Serialize(FArchive& Ar)
{
    Super::Serialize(Ar);

    int64 ScratchSpaceSize = 65536;
    Ar << ScratchSpaceSize;

    Ar.Serialize(&ScratchSpaceBuffer[0], ScratchSpaceSize);
}

