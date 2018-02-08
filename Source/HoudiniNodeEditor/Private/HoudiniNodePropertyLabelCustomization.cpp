#include "HoudiniNodePropertyLabelCustomization.h"
#include "HoudiniNodeEditorPrivatePCH.h"

#include "HoudiniNodePropertyLabel.h"


TSharedRef<IPropertyTypeCustomization>
FHoudiniNodePropertyLabelCustomization::MakeInstance() 
{
    return MakeShareable(new FHoudiniNodePropertyLabelCustomization);
}


void
FHoudiniNodePropertyLabelCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle,
    FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& PropertyTypeCustomizationUtils)
{
    UHoudiniNodePropertyLabel* Property = Cast<UHoudiniNodePropertyLabel>((*InPropertyHandle).GetProperty());
    if(!Property)
    {
        return;
    }

    const FString& PropertyName = Property->GetMetaData(TEXT("DisplayName"));
    FText LabelText = FText::FromString(PropertyName);

    HeaderRow
        .WholeRowContent()
        [
            SNew(STextBlock)
            .Text(LabelText)
            //.ToolTipText(ParameterLabelText)
            //.WrapTextAt(200)
            .Font(FEditorStyle::GetFontStyle(TEXT("PropertyWindow.NormalFont")))
            .Justification(ETextJustify::Center)
        ];
}


void
FHoudiniNodePropertyLabelCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle,
    IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& PropertyTypeCustomizationUtils)
{
    // No children.
}

