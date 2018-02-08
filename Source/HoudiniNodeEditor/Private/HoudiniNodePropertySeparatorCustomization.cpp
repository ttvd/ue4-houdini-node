#include "HoudiniNodePropertySeparatorCustomization.h"
#include "HoudiniNodeEditorPrivatePCH.h"


TSharedRef<IPropertyTypeCustomization>
FHoudiniNodePropertySeparatorCustomization::MakeInstance() 
{
    return MakeShareable(new FHoudiniNodePropertySeparatorCustomization);
}


void
FHoudiniNodePropertySeparatorCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle,
    FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& PropertyTypeCustomizationUtils)
{
    HeaderRow
        /*.NameContent()
        [
            StructPropertyHandle->CreatePropertyNameWidget()
        ]*/
        .ValueContent()
        .MinDesiredWidth(125.0f)
        .MaxDesiredWidth(600.0f)
        [
            SNew(SSeparator)
            .Orientation(Orient_Horizontal)
        ];
}


void
FHoudiniNodePropertySeparatorCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle,
    IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& PropertyTypeCustomizationUtils)
{
    // No children.
}

