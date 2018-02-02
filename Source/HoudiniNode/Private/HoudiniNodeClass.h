#pragma once
#include "HoudiniNodePrivatePCH.h"
#include "HoudiniNodeClass.generated.h"


class OBJ_Node;
class OP_OTLLibrary;
class UT_String;
class PRM_Template;
class PRM_Range;
class GU_Detail;
class GA_Primitive;

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

    //! Set cook time.
    void SetCookTime(float InTime);

    //! Return cook time.
    float GetCookTime() const;

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

    //! Return the underlying detail.
    GU_Detail* GetDetail() const;

public:

    //! Retrieve all points of this detail.
    bool GetAllPoints(TArray<GA_Offset>& Points) const;

    //! Retrieve all primitives of this detail.
    bool GetAllPrimitives(TArray<GA_Primitive*>& Primitives) const;

    //! Retrieve all primitives that are members of a given group.
    bool GetGroupPrimitives(const FString& GroupName, TArray<GA_Primitive*>& Primitives) const;

    //! Retrieve all primitives that are members of a given group and split by part.
    bool GetGroupPrimitives(const FString& GroupName, TMap<int32, TArray<GA_Primitive*> >& Parts) const;

    //! Get all parts.
    bool GetParts(TMap<int32, TArray<GA_Primitive*> >& Parts) const;

public:

    //! Create parameters.
    bool CreateParameters(UHoudiniNodeComponent* HoudiniNodeComponent);

public:

    //! Called whenever a property of this class changes. Return true if triggered cook was successful.
    bool OnParameterChanged(UProperty* Property);

protected:

    //! Create the underlying node with a given name.
    bool CreateNode(const UT_String& NodeName);

    //! Retrieve asset names for this Houdini node asset.
    bool GetAssetNames(TArray<UT_String>& AssetNames) const;

protected:

    //! Cook the detail at current time.
    bool CookDetail();

    //! Reset cooked detail.
    void ResetDetail();

protected:

    //! Create a parameter from a given template.
    int32 CreateParameter(const PRM_Template* Template);

protected:

    //! List of generated properties during the last cook.
    TMap<FString, UProperty*> Properties;

protected:

    //! Corresponding Houdini object node.
    OBJ_Node* Node;

    //! Corresponding loaded library.
    OP_OTLLibrary* Library;

protected:

    //! Corresponding Houdini detail handle.
    GU_DetailHandle DetailHandle;

    //! Corresponding Houdini detail of the active display node.
    GU_Detail* Detail;

protected:

    //! Associated Houdini component.
    UHoudiniNodeComponent* Component;

    //! Path of the library file used to load the library.
    FString LibraryPath;

    //! Cook time.
    float Time;
};


