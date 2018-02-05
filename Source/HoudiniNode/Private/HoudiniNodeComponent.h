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

    FMemory::Memcpy((void*) PositionNew, (const void*) Values, Bytes);

    const uint32 ScratchSpaceOffset = offsetof(UHoudiniNodeComponent, ScratchSpaceBuffer);
    const uint32 ScratchSpaceOffsetComputed = (uint32)(PositionNew - ScratchSpaceBufferStart);

    ScratchSpaceBufferOffset = ScratchSpaceOffsetComputed + Bytes;
    return ScratchSpaceOffset + ScratchSpaceOffsetComputed;
}


template<>
inline
uint32
UHoudiniNodeComponent::SetScratchSpaceValues<FString>(const TArray<FString>& Values)
{
    check(Values.Num() > 0);

    char* ScratchSpaceBufferStart = (char*) &ScratchSpaceBuffer[0];

    char* PositionNew = ScratchSpaceBufferStart + ScratchSpaceBufferOffset;
    PositionNew = (char*) Align<FString*>((FString*) PositionNew, alignof(FString));

    for(int32 Idx = 0; Idx < Values.Num(); ++Idx)
    {
        const FString& Value = Values[Idx];
        new(PositionNew) FString(Value);
        PositionNew += sizeof(FString);
    }

    const uint32 ScratchSpaceOffset = offsetof(UHoudiniNodeComponent, ScratchSpaceBuffer);
    const uint32 ScratchSpaceOffsetComputed = (uint32)(PositionNew - ScratchSpaceBufferStart);

    ScratchSpaceBufferOffset = ScratchSpaceOffsetComputed + sizeof(FString) * Values.Num();
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

    FMemory::Memcpy((void*) Position, (const void*) Values, Bytes);
}


template <>
inline
void
UHoudiniNodeComponent::SetScratchSpaceValuesAtOffset<FString>(const TArray<FString>& Values, uint32 Offset)
{
    check(Values.Num() > 0);

    char* Position = (char*) this;
    Position += Offset;

    for(int32 Idx = 0; Idx < Values.Num(); ++Idx)
    {
        const FString& Value = Values[Idx];
        new(Position) FString(Value);
        Position += sizeof(FString);
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
UHoudiniNodeComponent::SetScratchSpaceValueAtOffset(TType Values, uint32 Offset)
{
    SetScratchSpaceValuesAtOffset(&Value, sizeof(TType), Offset);
}
