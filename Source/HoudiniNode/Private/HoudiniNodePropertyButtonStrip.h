#pragma once
#include "HoudiniNodePropertyInt.h"
#include "HoudiniNodePropertyButtonStrip.generated.h"


class PRM_Template;
class UHoudiniNodeComponent;


UCLASS()
class HOUDININODE_API UHoudiniNodePropertyButtonStrip : public UHoudiniNodePropertyInt
{
    GENERATED_UCLASS_BODY()
    virtual ~UHoudiniNodePropertyButtonStrip();

public:

    //! Retrieve button names.
    virtual bool GetButtonNames(TArray<FString>& ButtonNames) const;
};

