#pragma once
#include "HoudiniNodeEditorModuleInterface.h"


class MOT_Director;
class OP_Network;


class HOUDININODEEDITOR_API FHoudiniNodeEditor : public IHoudiniNodeEditorModuleInterface
{
public:

    FHoudiniNodeEditor();
    ~FHoudiniNodeEditor();

public:

    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};


extern HOUDININODEEDITOR_API FHoudiniNodeEditor* GHoudiniNodeEditor;
