#pragma once
#include "HoudiniNodeActorFactory.generated.h"


UCLASS(config=Editor)
class UHoudiniNodeActorFactory : public UActorFactory
{
    GENERATED_UCLASS_BODY()
    virtual ~UHoudiniNodeActorFactory();

public:

    //! Return true if Actor can be created from a given Houdini node asset.
    virtual bool CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg) override;

    //! Given an actor instance, return the corresponding original asset.
    virtual UObject* GetAssetFromActorInstance(AActor* Actor) override;

    //! Invoked after after Houdini node actor it has been spawned to assign a Houdini node asset to it.
    virtual void PostSpawnActor(UObject* Asset, AActor* Actor) override;
};

