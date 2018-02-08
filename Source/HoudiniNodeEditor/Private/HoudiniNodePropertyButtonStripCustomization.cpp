#include "HoudiniNodePropertyButtonStripCustomization.h"
#include "HoudiniNodePropertyButtonStrip.h"
#include "HoudiniNodeEditorPrivatePCH.h"


TSharedRef<IPropertyTypeCustomization>
FHoudiniNodePropertyButtonStripCustomization::MakeInstance() 
{
    return MakeShareable(new FHoudiniNodePropertyButtonStripCustomization);
}


void
FHoudiniNodePropertyButtonStripCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle,
    FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& PropertyTypeCustomizationUtils)
{
    UHoudiniNodePropertyButtonStrip* Property = Cast<UHoudiniNodePropertyButtonStrip>((*InPropertyHandle).GetProperty());
    if(!Property)
    {
        return;
    }

    TArray<FString> ButtonNames;
    if(!Property->GetButtonNames(ButtonNames))
    {
        return;
    }

    TSharedPtr<SUniformGridPanel> ButtonsPanel;

    HeaderRow
    .WholeRowContent()
    [
        SAssignNew(ButtonsPanel, SUniformGridPanel)
    ];

    const int32 PropertySize = Property->GetPropertyDim();
    for(int32 Idx = 0; Idx < PropertySize; ++Idx)
    {
        const FString& ButtonName = ButtonNames[Idx];
        FText ButtonText = FText::FromString(ButtonName);

        ButtonsPanel->AddSlot(Idx, 0)
        [
            SNew(SCheckBox)
            //.IsChecked(this, &FMobilityCustomization::IsMobilityActive, EComponentMobility::Stationary)
            .Style(FEditorStyle::Get(), "Property.ToggleButton.Middle")
            [
                SNew(SHorizontalBox)
                +SHorizontalBox::Slot()
                .AutoWidth()
                .VAlign(VAlign_Center)
                .Padding(3, 2)
                [
                    SNew(SImage)
                    .Image(FEditorStyle::GetBrush("Mobility.Movable"))
                ]

                +SHorizontalBox::Slot()
                .FillWidth(1.0f)
                .VAlign(VAlign_Center)
                .HAlign(HAlign_Center)
                .Padding(6, 2)
                [
                    SNew(STextBlock)
                    .Text(ButtonText)
                    .Font(IDetailLayoutBuilder::GetDetailFont())
                    //.ColorAndOpacity(this, &FMobilityCustomization::GetMobilityTextColor, EComponentMobility::Movable)
                ]
            ]
        ];
    }
}


void
FHoudiniNodePropertyButtonStripCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle,
    IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& PropertyTypeCustomizationUtils)
{
    // No children.
}


