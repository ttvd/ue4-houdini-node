#pragma once
#include "HoudiniNodeActor.generated.h"


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
    UHoudiniNodeAsset* Asset;

    //! Asset cook time.
    UPROPERTY(Category = HoudiniNode, EditAnywhere)
    float Time;

    //! Asset scale.
    UPROPERTY(Category = HoudiniNode, EditAnywhere)
    float Scale;

    //! Assigned Houdini Node component.
    UPROPERTY(Category=HoudiniNode, VisibleAnywhere)
    UHoudiniNodeComponent* HoudiniNodeComponent;

public:

    //! Register generated objects with this actor.
    void RegisterGeneratedActors(const TMap<FString, TArray<AActor*> >& GeneratedActors);

public:

#if WITH_EDITOR

    //! Called whenever a property on the actor changes.
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

#endif

};


