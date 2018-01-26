#pragma once
#include "HoudiniNodeActor.generated.h"


class OBJ_Node;

class UHoudiniNodeAsset;
class UHoudiniNodeComponent;


UCLASS()
class HOUDININODE_API AHoudiniNodeActor : public AActor
{
    GENERATED_UCLASS_BODY()
    virtual ~AHoudiniNodeActor();

public:

    //! Assigned Houdini Node asset.
    UPROPERTY(Category=HoudiniNode, EditAnywhere)
    UHoudiniNodeAsset* HoudiniNodeAsset;

    //! Assigned Houdini Node component.
    UPROPERTY(Category=HoudiniNode, VisibleAnywhere)
    UHoudiniNodeComponent* HoudiniNodeComponent;

public:

    virtual void PostActorCreated() override;

protected:

    //! Corresponding Houdini object node.
    OBJ_Node* Node;
};


