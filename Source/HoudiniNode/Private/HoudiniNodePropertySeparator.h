#pragma once
#include "HoudiniNodePropertyCommon.h"
#include "HoudiniNodePropertyInterface.h"
#include "HoudiniNodePropertySeparator.generated.h"


class PRM_Template;
class OP_Node;

class UHoudiniNodeComponent;


UCLASS()
class HOUDININODE_API UHoudiniNodePropertySeparator : public UFloatProperty, public FHoudiniNodePropertyCommon, public IHoudiniNodePropertyInterface
{
    GENERATED_UCLASS_BODY()
    virtual ~UHoudiniNodePropertySeparator();

public:

    //! Construct float property from a given template.
    virtual bool Construct(OP_Node* Node, const PRM_Template* Template, UHoudiniNodeComponent* Component, float Time) override;

    //! Update property.
    virtual bool Update(OP_Node* Node, float Time) override;

    //! Upload property value.
    virtual bool Upload(OP_Node* Node, float Time) override;
};

