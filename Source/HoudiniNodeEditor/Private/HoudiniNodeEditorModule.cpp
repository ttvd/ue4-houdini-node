#include "HoudiniNodeEditorModule.h"
#include "HoudiniNodeEditorPrivatePCH.h"
#include "HoudiniNodeActorFactory.h"


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

    // RegisterCustomClassLayout
}


void
FHoudiniNodeEditor::UnregisterPropertyCustomizations()
{
    if(FModuleManager::Get().IsModuleLoaded(TEXT("PropertyEditor")))
    {
        FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>(TEXT("PropertyEditor"));
        //UnregisterCustomClassLayout
    }
}


IMPLEMENT_MODULE(FHoudiniNodeEditor, HoudiniNodeEditor);
