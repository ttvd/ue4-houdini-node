#pragma once
#include "HoudiniNodeClass.generated.h"


class OBJ_Node;
class UHoudiniNodeAsset;


UCLASS()
class HOUDININODE_API UHoudiniNodeClass : public UClass
{
    GENERATED_UCLASS_BODY()
    virtual ~UHoudiniNodeClass();

protected:

    //! Associated Houdini node asset.
    UPROPERTY()
    UHoudiniNodeAsset* HoudiniNodeAsset;

protected:

    //! List of generated properties.
    TMap<FString, UProperty*> Properties;

protected:

    //! Corresponding Houdini object node.
    OBJ_Node* Node;
};
