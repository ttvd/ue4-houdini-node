#include "HoudiniNodePrivatePCH.h"
#include "HoudiniNodeComponent.h"


UHoudiniNodeComponent::UHoudiniNodeComponent(const FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer),
    ScratchSpaceBufferOffset(0u)
{

}


UHoudiniNodeComponent::~UHoudiniNodeComponent()
{

}


char*
UHoudiniNodeComponent::GetCurrentScratchSpacePosition() const
{
    if(ScratchSpaceBufferOffset >= HOUDINI_NODE_SCRATCH_SPACE_BUFFER_SIZE)
    {
        return nullptr;
    }

    return (char*)(&ScratchSpaceBuffer[0] + ScratchSpaceBufferOffset);
}


void
UHoudiniNodeComponent::IncrementScratchSpaceBufferOffset(uint32 Offset)
{
    ScratchSpaceBufferOffset += Offset;
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


uint32
UHoudiniNodeComponent::GetCurrentScratchSpaceOffset() const
{
    uint32 Offset = offsetof(UHoudiniNodeComponent, ScratchSpaceBuffer);
    Offset += ScratchSpaceBufferOffset;

    return Offset;
}

