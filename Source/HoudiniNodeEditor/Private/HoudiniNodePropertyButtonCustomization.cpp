#include "HoudiniNodePropertyButtonCustomization.h"
#include "HoudiniNodePropertyButton.h"
#include "HoudiniNodeEditorPrivatePCH.h"


TSharedRef<IPropertyTypeCustomization>
FHoudiniNodePropertyButtonCustomization::MakeInstance() 
{
    return MakeShareable(new FHoudiniNodePropertyButtonCustomization);
}


void
FHoudiniNodePropertyButtonCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle,
    FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& PropertyTypeCustomizationUtils)
{
    UHoudiniNodePropertyButton* Property = Cast<UHoudiniNodePropertyButton>((*InPropertyHandle).GetProperty());
    if(!Property)
    {
        return;
    }

    const FString& PropertyName = Property->GetMetaData(TEXT("DisplayName"));
    FText ButtonText = FText::FromString(PropertyName);

    HeaderRow
        .WholeRowContent()
        [
            SNew(SVerticalBox)
            +SVerticalBox::Slot()
            .AutoHeight()
            .Padding(4, 4)
            .HAlign(HAlign_Center)
            .VAlign(VAlign_Center)
            [
                SNew(SButton)
                .Text(ButtonText)
                .OnClicked(this, &FHoudiniNodePropertyButtonCustomization::OnButtonClicked, Property)
            ]
        ];
}


void
FHoudiniNodePropertyButtonCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle,
    IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& PropertyTypeCustomizationUtils)
{
    // No children.
}


FReply
FHoudiniNodePropertyButtonCustomization::OnButtonClicked(UHoudiniNodePropertyButton* Property)
{
    if(Property)
    {
        Property->Press();
    }

    return FReply::Handled();
}

