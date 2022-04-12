#pragma once
#include "HoudiniNodePropertyInt.h"
#include "HoudiniNodePropertyButton.generated.h"


class PRM_Template;
class UHoudiniNodeComponent;


UCLASS()
class HOUDININODE_API UHoudiniNodePropertyButton : public UHoudiniNodePropertyInt
{
    GENERATED_UCLASS_BODY()
    virtual ~UHoudiniNodePropertyButton();

public:

    //! Handle button press.
    virtual bool Press();
};

