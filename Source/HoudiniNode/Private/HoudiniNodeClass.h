#pragma once
#include "HoudiniNodePrivatePCH.h"
#include "HoudiniNodeDetail.h"
#include "HoudiniNodeClass.generated.h"


class OBJ_Node;
class OP_OTLLibrary;
class UT_String;
class PRM_Template;
class PRM_Range;

class UHoudiniNodeAsset;
class UHoudiniNodeComponent;
class FHoudiniNodePropertyCommon;
class IHoudiniNodePropertyInterface;


UCLASS()
class HOUDININODE_API UHoudiniNodeClass : public UClass
{
    GENERATED_UCLASS_BODY()
    virtual ~UHoudiniNodeClass();

    friend class UHoudiniNodeComponent;

public:

    //! Associated Houdini node asset.
    UPROPERTY()
    UHoudiniNodeAsset* HoudiniNodeAsset;

public:

    //! Return the owner actor.
    AHoudiniNodeActor* GetHoudiniNodeActor() const;

public:

    //! Set cook time.
    void SetCookTime(float InTime);

    //! Return cook time.
    float GetCookTime() const;

public:

    //! Set scale.
    void SetScale(float InScale);

    //! Get scale.
    float GetScale() const;

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

    //! Return current detail.
    FHoudiniNodeDetail& GetDetail() const;

public:

    //! Create parameters.
    bool CreateParameters(UHoudiniNodeComponent* HoudiniNodeComponent);

    //! Cook the detail at present time.
    bool CookDetail();

public:

    //! Called whenever a property of this class changes. Return true if triggered cook was successful.
    bool OnParameterChanged(UProperty* Property);

protected:

    //! Called on successful cook. We generate geometry here.
    void OnCookComplete();

protected:

    //! Create the underlying node with a given name.
    bool CreateNode(const UT_String& NodeName);

    //! Retrieve asset names for this Houdini node asset.
    bool GetAssetNames(TArray<UT_String>& AssetNames) const;

protected:

    //! Reset cooked detail.
    void ResetDetail();

protected:

    //! Create a parameter from a given template.
    int32 CreateParameter(const PRM_Template* Template, TArray<IHoudiniNodePropertyInterface*>& CreatedProperties);

protected:

    //! List of generated properties during the last cook.
    TMap<FString, IHoudiniNodePropertyInterface*> Properties;

protected:

    //! Corresponding Houdini object node.
    OBJ_Node* Node;

    //! Corresponding loaded library.
    OP_OTLLibrary* Library;

protected:

    //! Detail for the display node.
    TSharedPtr<FHoudiniNodeDetail> Detail;

protected:

    //! Associated Houdini component.
    UHoudiniNodeComponent* Component;

    //! Path of the library file used to load the library.
    FString LibraryPath;

    //! Cook time.
    float Time;

    //! Scale.
    float Scale;
};


