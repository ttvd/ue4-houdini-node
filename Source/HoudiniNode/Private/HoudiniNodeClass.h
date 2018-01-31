#pragma once
#include "HoudiniNodeClass.generated.h"


class OBJ_Node;
class OP_OTLLibrary;
class UT_String;
class PRM_Template;

class UHoudiniNodeAsset;
class UHoudiniNodeComponent;


UCLASS()
class HOUDININODE_API UHoudiniNodeClass : public UClass
{
    GENERATED_UCLASS_BODY()
    virtual ~UHoudiniNodeClass();

public:

    //! Associated Houdini node asset.
    UPROPERTY()
    UHoudiniNodeAsset* HoudiniNodeAsset;

public:

    //! Create library for the underlying asset.
    bool AddLibrary();

    //! Remove library for the underlying asset.
    bool RemoveLibrary();

    //! Return true if the library for the underlying asset has been created.
    bool HasLibrary() const;

public:

    //! Create the underlying node.
    bool CreateNode();

    //! Destroy the underlying node.
    bool DestroyNode();

    //! Return the underlying node.
    OBJ_Node* GetNode() const;

public:

    //! Create parameters.
    bool CreateParameters(UHoudiniNodeComponent* HoudiniNodeComponent);

protected:

    //! Create the underlying node with a given name.
    bool CreateNode(const UT_String& NodeName);

    //! Retrieve asset names for this Houdini node asset.
    bool GetAssetNames(TArray<UT_String>& AssetNames) const;

protected:

    //! Create a parameter from a given template.
    int32 CreateParameter(const PRM_Template* Template);

    //! Create a float type parameter from a given template.
    int32 CreateParameterFloat(const PRM_Template* Template);

protected:

    //! List of generated properties during the last cook.
    TMap<FString, UProperty*> Properties;

protected:

    //! Corresponding Houdini object node.
    OBJ_Node* Node;

    //! Corresponding loaded library.
    OP_OTLLibrary* Library;

    //! Associated Houdini component.
    UHoudiniNodeComponent* Component;

    //! Path of the library file used to load the library.
    FString LibraryPath;

    //! Cook time.
    float Time;
};
