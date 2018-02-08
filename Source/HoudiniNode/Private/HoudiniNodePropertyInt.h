#pragma once
#include "HoudiniNodePropertyCommon.h"
#include "HoudiniNodePropertyInterface.h"
#include "HoudiniNodePropertyInt.generated.h"


class PRM_Template;
class OP_Node;

class UHoudiniNodeComponent;


UCLASS()
class HOUDININODE_API UHoudiniNodePropertyInt : public UIntProperty, public FHoudiniNodePropertyCommon, public IHoudiniNodePropertyInterface
{
    GENERATED_UCLASS_BODY()
    virtual ~UHoudiniNodePropertyInt();

public:

    //! Construct float property from a given template.
    virtual bool Construct(const PRM_Template* Template, UHoudiniNodeComponent* Component) override;

    //! Update property.
    virtual bool Update() override;

    //! Upload property value.
    virtual bool Upload() override;
};

