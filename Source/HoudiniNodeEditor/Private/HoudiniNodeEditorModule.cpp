#include "HoudiniNodeEditorPrivatePCH.h"
#include "HoudiniNodeEditorModule.h"


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
}


void
FHoudiniNodeEditor::ShutdownModule()
{
}


IMPLEMENT_MODULE(FHoudiniNodeEditor, HoudiniNodeEditor);
