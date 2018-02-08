#pragma once
#include "HoudiniNodePropertyCommon.h"
#include "HoudiniNodePropertyInterface.h"
#include "HoudiniNodePropertyString.generated.h"


class PRM_Template;
class UHoudiniNodeComponent;


UCLASS()
class HOUDININODE_API UHoudiniNodePropertyString : public UStrProperty, public FHoudiniNodePropertyCommon, public IHoudiniNodePropertyInterface
{
    GENERATED_UCLASS_BODY()
    virtual ~UHoudiniNodePropertyString();

public:

    //! Construct float property from a given template.
    virtual bool Construct(const PRM_Template* Template, UHoudiniNodeComponent* Component) override;

    //! Update property.
    virtual bool Update() override;

    //! Upload property value.
    virtual bool Upload() override;
};

