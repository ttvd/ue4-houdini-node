#pragma once
#include "HoudiniNodeActor.generated.h"


UCLASS()
class HOUDININODE_API AHoudiniNodeActor : public AActor
{
    GENERATED_UCLASS_BODY()
    virtual ~AHoudiniNodeActor();

public:

    UPROPERTY(Category=HoudiniNode, EditAnywhere)
    bool bSomething;
};
