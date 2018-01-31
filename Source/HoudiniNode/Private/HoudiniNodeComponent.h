#pragma once
#include "HoudiniNodeComponent.generated.h"


UCLASS()
class HOUDININODE_API UHoudiniNodeComponent : public USceneComponent
{
    GENERATED_UCLASS_BODY()
    virtual ~UHoudiniNodeComponent();

public:

    virtual void Serialize(FArchive& Ar) override;

public:

    //! Set a value (with a proper alignment).
    template<typename TType> uint32 SetScratchSpaceValues(TType* Values, uint32 Bytes);
    template<typename TType> uint32 SetScratchSpaceValues(const TArray<TType>& Values);
    template<typename TType> uint32 SetScratchSpaceValue(TType Value);

protected:

    //! Scratch space buffer.
    char ScratchSpaceBuffer[HOUDINI_NODE_SCRATCH_SPACE_BUFFER_SIZE];

    //! Current scratch buffer offset.
    uint32 ScratchSpaceBufferOffset;
};


template<typename TType>
uint32
UHoudiniNodeComponent::SetScratchSpaceValues(TType* Values, uint32 Bytes)
{
    char* ScratchSpaceBufferStart = (char*) &ScratchSpaceBuffer[0];

    char* PositionNew = ScratchSpaceBufferStart + ScratchSpaceBufferOffset;
    PositionNew = (char*) Align<TType*>((TType*) PositionNew, alignof(TType));

    FMemory::Memcpy((void*) PositionNew, (const void*) Values, Bytes);

    const uint32 ScratchSpaceOffset = offsetof(UHoudiniNodeComponent, ScratchSpaceBuffer);
    const uint32 ScratchSpaceOffsetComputed = (uint32)(PositionNew - ScratchSpaceBufferStart);

    ScratchSpaceBufferOffset = ScratchSpaceOffsetComputed + Bytes;
    return ScratchSpaceOffset + ScratchSpaceOffsetComputed;
}


template<typename TType>
uint32
UHoudiniNodeComponent::SetScratchSpaceValues(const TArray<TType>& Values)
{
    if(Values.Num() > 0)
    {
        return SetScratchSpaceValues(&Values[0], sizeof(TType) * Values.Num());
    }

    return 0u;
}


template<typename TType>
uint32
UHoudiniNodeComponent::SetScratchSpaceValue(TType Value)
{
    return SetScratchSpaceValues(&Value, sizeof(TType));
}
