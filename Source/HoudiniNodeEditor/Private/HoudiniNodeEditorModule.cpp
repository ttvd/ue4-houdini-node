#include "HoudiniNodeEditorPrivatePCH.h"
#include "HoudiniNodeEditorModule.h"
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
}


void
FHoudiniNodeEditor::ShutdownModule()
{
}


IMPLEMENT_MODULE(FHoudiniNodeEditor, HoudiniNodeEditor);
