#include "HoudiniNodePropertyPathCustomization.h"
#include "HoudiniNodeEditorPrivatePCH.h"


TSharedRef<IPropertyTypeCustomization>
FHoudiniNodePropertyPathCustomization::MakeInstance() 
{
    return MakeShareable(new FHoudiniNodePropertyPathCustomization);
}


void
FHoudiniNodePropertyPathCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle,
    FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& PropertyTypeCustomizationUtils)
{
    /*
    HeaderRow
    .WholeRowContent()
    [
        SNew(SSeparator)
        .Orientation(Orient_Horizontal)
    ];
    */
}


void
FHoudiniNodePropertyPathCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle,
    IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& PropertyTypeCustomizationUtils)
{
    // No children.
}

