#pragma once
#include "HoudiniNodePropertyString.h"
#include "HoudiniNodePropertySeparator.generated.h"


class PRM_Template;
class OP_Node;

class UHoudiniNodeComponent;


UCLASS()
class HOUDININODE_API UHoudiniNodePropertySeparator : public UHoudiniNodePropertyString
{
    GENERATED_UCLASS_BODY()
    virtual ~UHoudiniNodePropertySeparator();
};

