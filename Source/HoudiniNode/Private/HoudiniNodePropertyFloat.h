#pragma once
#include "HoudiniNodePropertyCommon.h"
#include "HoudiniNodePropertyFloat.generated.h"


class PRM_Template;
class OP_Node;

class UHoudiniNodeComponent;


UCLASS()
class HOUDININODE_API UHoudiniNodePropertyFloat : public UFloatProperty, public FHoudiniNodePropertyCommon
{
    GENERATED_UCLASS_BODY()
    virtual ~UHoudiniNodePropertyFloat();

public:

    //! Construct float property from a given template.
    bool Construct(OP_Node* Node, const PRM_Template* Template, UHoudiniNodeComponent* Component, float Time);
};

