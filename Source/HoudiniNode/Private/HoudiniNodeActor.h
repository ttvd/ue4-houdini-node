#pragma once
#include "HoudiniNodeActor.generated.h"


class OBJ_Node;


UCLASS()
class HOUDININODE_API AHoudiniNodeActor : public AActor
{
    GENERATED_UCLASS_BODY()
    virtual ~AHoudiniNodeActor();

public:

    UPROPERTY(Category=HoudiniNode, EditAnywhere)
    bool bSomething;

protected:

    //! Corresponding Houdini object node.
    OBJ_Node* Node;
};
