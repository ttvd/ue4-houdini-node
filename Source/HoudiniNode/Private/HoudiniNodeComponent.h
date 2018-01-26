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

    //! Scratch space buffer.
    char ScratchSpaceBuffer[65536];
};
