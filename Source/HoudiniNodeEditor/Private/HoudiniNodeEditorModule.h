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

protected:

    //! Register property customizations.
    void RegisterPropertyCustomizations();

    //! Unregister property customizations.
    void UnregisterPropertyCustomizations();
};


extern HOUDININODEEDITOR_API FHoudiniNodeEditor* GHoudiniNodeEditor;
