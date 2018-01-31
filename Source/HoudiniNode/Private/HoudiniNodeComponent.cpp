#include "HoudiniNodeComponent.h"
#include "HoudiniNodePrivatePCH.h"


UHoudiniNodeComponent::UHoudiniNodeComponent(const FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer),
    ScratchSpaceBufferOffset(0u)
{

}


UHoudiniNodeComponent::~UHoudiniNodeComponent()
{

}


void
UHoudiniNodeComponent::Serialize(FArchive& Ar)
{
    Super::Serialize(Ar);

    uint32 ScratchSpaceSize = HOUDINI_NODE_SCRATCH_SPACE_BUFFER_SIZE;
    Ar << ScratchSpaceSize;

    Ar << ScratchSpaceBufferOffset;

    Ar.Serialize(&ScratchSpaceBuffer[0], ScratchSpaceSize);
}

