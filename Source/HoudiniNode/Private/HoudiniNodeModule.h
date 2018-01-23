#pragma once
#include "HoudiniNodeModuleInterface.h"


class MOT_Director;
class OP_Network;


class HOUDININODE_API FHoudiniNode : public IHoudiniNodeModuleInterface
{
public:

    FHoudiniNode();
    ~FHoudiniNode();

public:

    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

public:

    //! Return top level object network.
    OP_Network* GetObjNetwork() const;

protected:

    //! MOT director.
    MOT_Director* Director;
};


extern HOUDININODE_API FHoudiniNode* GHoudiniNode;
