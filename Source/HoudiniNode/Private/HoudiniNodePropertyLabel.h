#pragma once
#include "HoudiniNodePropertyString.h"
#include "HoudiniNodePropertyLabel.generated.h"


class PRM_Template;
class OP_Node;

class UHoudiniNodeComponent;


UCLASS()
class HOUDININODE_API UHoudiniNodePropertyLabel : public UHoudiniNodePropertyString
{
    GENERATED_UCLASS_BODY()
    virtual ~UHoudiniNodePropertyLabel();
};

