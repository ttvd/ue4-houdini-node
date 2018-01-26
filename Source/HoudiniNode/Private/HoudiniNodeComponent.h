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

    //! Return current scratch buffer pointer.
    char* GetCurrentScratchSpacePosition() const;

    //! Return current offset.
    uint32 GetCurrentScratchSpaceOffset() const;

public:

    //! Increment scratch buffer offset.
    void IncrementScratchSpaceBufferOffset(uint32 Offset);

    //! Increment scratch buffer offset for a given type.
    template<typename TType> void IncrementScratchSpaceBufferOffset();

protected:

    //! Scratch space buffer.
    char ScratchSpaceBuffer[65536u];

    //! Current scratch buffer offset.
    uint32 ScratchSpaceBufferOffset;
};


template<typename TType>
void
UHoudiniNodeComponent::IncrementScratchSpaceBufferOffset()
{
    const uint32 TypeSize = sizeof(TType);
    IncrementScratchSpaceBufferOffset(TypeSize);
}
