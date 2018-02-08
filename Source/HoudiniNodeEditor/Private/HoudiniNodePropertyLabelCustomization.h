#pragma once
#include "IPropertyTypeCustomization.h"

class IPropertyHandle;
class FDetailWidgetRow;
class IDetailChildrenBuilder;
class IPropertyTypeCustomizationUtils;


class FHoudiniNodePropertyLabelCustomization : public IPropertyTypeCustomization
{
public:

    static TSharedRef<IPropertyTypeCustomization> MakeInstance();

public:

    virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& HeaderRow,
        IPropertyTypeCustomizationUtils& PropertyTypeCustomizationUtils) override;

    virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle,
        IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& PropertyTypeCustomizationUtils) override;
};

