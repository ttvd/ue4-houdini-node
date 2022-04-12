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

#if WITH_EDITOR

    //! Called whenever a property on the actor changes.
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

#endif

public:

    //! Set a value (with a proper alignment) and return the offset.
    template<typename TType> uint32 SetScratchSpaceValues(TType* Values, uint32 Bytes);
    template<typename TType> uint32 SetScratchSpaceValues(const TArray<TType>& Values);
    template<typename TType> uint32 SetScratchSpaceValue(TType Value);

public:

    //! Set a value at the given offset.
    template <typename TType> void SetScratchSpaceValuesAtOffset(TType* Values, uint32 Bytes, uint32 Offset);
    template <typename TType> void SetScratchSpaceValuesAtOffset(const TArray<TType>& Values, uint32 Offset);
    template <typename TType> void SetScratchSpaceValueAtOffset(TType Values, uint32 Offset);

public:

    //! Get a value at the given offset.
    template <typename TType> void GetScratchSpaceValuesAtOffset(uint32 Offset, int32 Dim, TArray<TType>& Values);
    template <typename TType> void GetScratchSpaceValueAtOffset(uint32 Offset, TType& Value);

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
    check(Values);
    check(Bytes > 0u);

    char* ScratchSpaceBufferStart = (char*) &ScratchSpaceBuffer[0];

    char* PositionNew = ScratchSpaceBufferStart + ScratchSpaceBufferOffset;
    PositionNew = (char*) Align<TType*>((TType*) PositionNew, alignof(TType));

    const uint32 EntrySize = sizeof(TType);

    if(EntrySize <= 4)
    {
        FMemory::Memcpy((void*) PositionNew, (const void*) Values, Bytes);
    }
    else
    {
        const int32 NumEntries = Bytes / EntrySize;
        char* PositionElement = PositionNew;

        for(int32 Idx = 0; Idx < NumEntries; ++Idx)
        {
            const TType& Value = *(Values + Idx);
            new(PositionElement) TType(Value);
            PositionElement += sizeof(TType);
        }
    }

    const uint32 ScratchSpaceOffset = offsetof(UHoudiniNodeComponent, ScratchSpaceBuffer);
    const uint32 ScratchSpaceOffsetComputed = (uint32)(PositionNew - ScratchSpaceBufferStart);

    ScratchSpaceBufferOffset = ScratchSpaceOffsetComputed + Bytes;
    return ScratchSpaceOffset + ScratchSpaceOffsetComputed;
}


template<typename TType>
uint32
UHoudiniNodeComponent::SetScratchSpaceValues(const TArray<TType>& Values)
{
    check(Values.Num() > 0);
    return SetScratchSpaceValues(&Values[0], sizeof(TType) * Values.Num());
}


template<typename TType>
uint32
UHoudiniNodeComponent::SetScratchSpaceValue(TType Value)
{
    return SetScratchSpaceValues(&Value, sizeof(TType));
}


template <typename TType>
void
UHoudiniNodeComponent::SetScratchSpaceValuesAtOffset(TType* Values, uint32 Bytes, uint32 Offset)
{
    check(Values);
    check(Bytes > 0u);

    char* Position = (char*) this;
    Position += Offset;

    const int32 EntrySize = sizeof(TType);

    if(EntrySize <= 4)
    {
        FMemory::Memcpy((void*) Position, (const void*) Values, Bytes);
    }
    else
    {
        const int32 NumEntries = Bytes / EntrySize;

        for(int32 Idx = 0; Idx < NumEntries; ++Idx)
        {
            const TType& Value = *(Values + Idx);
            new(Position) TType(Value);
            Position += sizeof(TType);
        }
    }
}


template <typename TType>
void
UHoudiniNodeComponent::SetScratchSpaceValuesAtOffset(const TArray<TType>& Values, uint32 Offset)
{
    check(Values.Num() > 0);
    SetScratchSpaceValuesAtOffset(&Values[0], sizeof(TType) * Values.Num(), Offset);
}


template <typename TType>
void
UHoudiniNodeComponent::SetScratchSpaceValueAtOffset(TType Value, uint32 Offset)
{
    SetScratchSpaceValuesAtOffset(&Value, sizeof(TType), Offset);
}


template <typename TType>
void
UHoudiniNodeComponent::GetScratchSpaceValuesAtOffset(uint32 Offset, int32 NumEntries, TArray<TType>& Values)
{
    if(NumEntries > 0)
    {
        Values.SetNumZeroed(NumEntries);

        char* Position = (char*) this;
        Position += Offset;

        const int32 EntrySize = sizeof(TType);
        const int32 Bytes = EntrySize * NumEntries;

        if(EntrySize <= 4)
        {
            FMemory::Memcpy((void*) &Values[0], (const void*) Position, Bytes);
        }
        else
        {
            for(int32 Idx = 0; Idx < NumEntries; ++Idx)
            {
                TType Value = *((TType*) Position + Idx);
                Values[Idx] = Value;
                Position += sizeof(TType);
            }
        }
    }
}


template <typename TType>
void
UHoudiniNodeComponent::GetScratchSpaceValueAtOffset(uint32 Offset, TType& Value)
{
    char* Position = (char*) this;
    Position += Offset;

    const int32 EntrySize = sizeof(TType);

    if(EntrySize <= 4)
    {
        FMemory::Memcpy((void*) &Value, (const void*) Position, Bytes);
    }
    else
    {
        Value = *((TType*) Position);
    }
}
