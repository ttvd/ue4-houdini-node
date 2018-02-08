#include "HoudiniNodeEditorModule.h"
#include "HoudiniNodeEditorPrivatePCH.h"
#include "HoudiniNodeActorFactory.h"

#include "HoudiniNodePropertySeparator.h"
#include "HoudiniNodePropertySeparatorCustomization.h"

#include "HoudiniNodePropertyButton.h"
#include "HoudiniNodePropertyButtonCustomization.h"

#include "HoudiniNodePropertyButtonStrip.h"
#include "HoudiniNodePropertyButtonStripCustomization.h"

#include "HoudiniNodePropertyLabel.h"
#include "HoudiniNodePropertyLabelCustomization.h"


FHoudiniNodeEditor*
GHoudiniNodeEditor = nullptr;


FHoudiniNodeEditor::FHoudiniNodeEditor()
{

}


FHoudiniNodeEditor::~FHoudiniNodeEditor()
{
    GHoudiniNodeEditor = nullptr;
}


void
FHoudiniNodeEditor::StartupModule()
{
    GHoudiniNodeEditor = this;

    // Register our actor factory.
    {
        if(GEditor)
        {
            UHoudiniNodeActorFactory* Factory =
                NewObject<UHoudiniNodeActorFactory>(GetTransientPackage(), UHoudiniNodeActorFactory::StaticClass());

            GEditor->ActorFactories.Add(Factory);
        }
    }

    RegisterPropertyCustomizations();
}


void
FHoudiniNodeEditor::ShutdownModule()
{
    UnregisterPropertyCustomizations();
}


void
FHoudiniNodeEditor::RegisterPropertyCustomizations()
{
    FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>(TEXT("PropertyEditor"));

    PropertyModule.RegisterCustomPropertyTypeLayout(UHoudiniNodePropertySeparator::StaticClass()->GetFName(),
        FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FHoudiniNodePropertySeparatorCustomization::MakeInstance));

    PropertyModule.RegisterCustomPropertyTypeLayout(UHoudiniNodePropertyButton::StaticClass()->GetFName(),
        FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FHoudiniNodePropertyButtonCustomization::MakeInstance));

    PropertyModule.RegisterCustomPropertyTypeLayout(UHoudiniNodePropertyButtonStrip::StaticClass()->GetFName(),
        FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FHoudiniNodePropertyButtonStripCustomization::MakeInstance));

    PropertyModule.RegisterCustomPropertyTypeLayout(UHoudiniNodePropertyLabel::StaticClass()->GetFName(),
        FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FHoudiniNodePropertyLabelCustomization::MakeInstance));
}


void
FHoudiniNodeEditor::UnregisterPropertyCustomizations()
{
    if(FModuleManager::Get().IsModuleLoaded(TEXT("PropertyEditor")))
    {
        FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>(TEXT("PropertyEditor"));

        PropertyModule.UnregisterCustomPropertyTypeLayout(UHoudiniNodePropertySeparator::StaticClass()->GetFName());
        PropertyModule.UnregisterCustomPropertyTypeLayout(UHoudiniNodePropertyButton::StaticClass()->GetFName());
        PropertyModule.UnregisterCustomPropertyTypeLayout(UHoudiniNodePropertyButtonStrip::StaticClass()->GetFName());
        PropertyModule.UnregisterCustomPropertyTypeLayout(UHoudiniNodePropertyLabel::StaticClass()->GetFName());
    }
}


IMPLEMENT_MODULE(FHoudiniNodeEditor, HoudiniNodeEditor);
