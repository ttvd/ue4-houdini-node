#pragma once
#include "HoudiniNodeModuleInterface.h"


class MOT_Director;
class OP_Network;

class UHoudiniNodeGenerator;


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

    //! Return associated director.
    MOT_Director* GetDirector() const;

protected:

    //! Create generators.
    bool CreateGenerators();

protected:

    //! MOT director.
    MOT_Director* Director;

protected:

    //! List of available generators.
    TArray<UHoudiniNodeGenerator*> Generators;
};


extern HOUDININODE_API FHoudiniNode* GHoudiniNode;
