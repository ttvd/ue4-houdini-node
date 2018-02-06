#pragma once
#include "HoudiniNodeModuleInterface.h"


class MOT_Director;
class OP_Network;

class UHoudiniNodeGenerator;
class FReferenceCollector;
class UMaterialInterface;


class HOUDININODE_API FHoudiniNode : public IHoudiniNodeModuleInterface, public FGCObject
{
public:

    FHoudiniNode();
    ~FHoudiniNode();

public:

    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

public:

    virtual void AddReferencedObjects(FReferenceCollector& Collector) override;

public:

    //! Return top level object network.
    OP_Network* GetObjNetwork() const;

    //! Return associated director.
    MOT_Director* GetDirector() const;

public:

    //! Retrieve the list of available generators.
    const TArray<UHoudiniNodeGenerator*>& GetGenerators() const;

public:

    //! Return the default material.
    UMaterialInterface* GetDefaultMaterial() const;

protected:

    //! Create generators.
    bool CreateGenerators();

protected:

    //! MOT director.
    MOT_Director* Director;

protected:

    //! List of available generators.
    TArray<UHoudiniNodeGenerator*> Generators;

    //! Default material.
    UMaterialInterface* DefaultMaterial;
};


extern HOUDININODE_API FHoudiniNode* GHoudiniNode;
