#pragma once
#include "HoudiniNodePropertyString.h"
#include "HoudiniNodePropertyPath.generated.h"


class PRM_Template;
class OP_Node;

class UHoudiniNodeComponent;


UCLASS()
class HOUDININODE_API UHoudiniNodePropertyPath : public UHoudiniNodePropertyString
{
    GENERATED_UCLASS_BODY()
    virtual ~UHoudiniNodePropertyPath();
};

