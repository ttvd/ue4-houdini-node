#pragma once
#include "HoudiniNodeModuleInterface.h"


class MOT_Director;
class OP_Network;

class UHoudiniNodeGenerator;
class UHoudiniNodeObjectPacker;
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

    //! Retrieve the list of available object packers.
    const TMap<UClass*, UHoudiniNodeObjectPacker*>& GeObjectPackers() const;

public:

    //! Return the default material.
    UMaterialInterface* GetDefaultMaterial() const;

protected:

    //! Create generators.
    bool CreateGenerators();

    //! Create object packers.
    bool CreateObjectPackers();

protected:

    //! MOT director.
    MOT_Director* Director;

protected:

    //! List of available generators.
    TArray<UHoudiniNodeGenerator*> Generators;

    //! Available object packers.
    TMap<UClass*, UHoudiniNodeObjectPacker*> ObjectPackers;

    //! Default material.
    UMaterialInterface* DefaultMaterial;
};


extern HOUDININODE_API FHoudiniNode* GHoudiniNode;
