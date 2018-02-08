#pragma once
#include "HoudiniNodePropertyCommon.h"
#include "HoudiniNodePropertyInterface.h"
#include "HoudiniNodePropertyEnum.generated.h"


class PRM_Template;
class UHoudiniNodeComponent;


UCLASS()
class HOUDININODE_API UHoudiniNodePropertyEnum : public UEnumProperty, public FHoudiniNodePropertyCommon, public IHoudiniNodePropertyInterface
{
    GENERATED_UCLASS_BODY()
    virtual ~UHoudiniNodePropertyEnum();

public:

    //! Construct float property from a given template.
    virtual bool Construct(const PRM_Template* Template, UHoudiniNodeComponent* Component) override;

    //! Update property.
    virtual bool Update() override;

    //! Upload property value.
    virtual bool Upload() override;

protected:

    //! Retrieve a list of choice values.
    bool GetEnumValues(TArray<TPair<FName, int64> >& EnumValues) const;
};

