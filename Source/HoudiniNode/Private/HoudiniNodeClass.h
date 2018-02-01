#pragma once
#include "HoudiniNodeClass.generated.h"


class OBJ_Node;
class OP_OTLLibrary;
class UT_String;
class PRM_Template;
class PRM_Range;

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

    //! Common code to create a new property and set its parameters.
    template <typename TPropertyType, typename TType> TPropertyType* CreateParameterCommon(const PRM_Template* Template, const TArray<TType>& Values);
    template <typename TPropertyType, typename TType> TPropertyType* CreateParameterCommon(const PRM_Template* Template, TType Value);


protected:

    //! Assign offset for a given property.
    void AssignPropertyOffset(UProperty* Property, uint32 Offset) const;

    //! Assign meta tags for a given property.
    void AssignPropertyMeta(UProperty* Property, const PRM_Template* Template) const;

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


template <typename TPropertyType, typename TType>
TPropertyType*
UHoudiniNodeClass::CreateParameterCommon(const PRM_Template* Template, const TArray<TType>& Values)
{
    check(Component);
    check(Template);

    const PRM_Name* TemplateName = Template->getNamePtr();

    const UT_String& Name = TemplateName->getToken();
    const UT_String& Label = TemplateName->getLabel();

    static const EObjectFlags PropertyObjectFlags = RF_Public | RF_Transient;
    FString PropertyName = UTF8_TO_TCHAR(Name.c_str());

    TPropertyType* Property = NewObject<TPropertyType>(this, *PropertyName, PropertyObjectFlags);
    if(Property)
    {
        Property->ArrayDim = Values.Num();
        Property->PropertyFlags = UINT64_C(69793219077);
        Property->PropertyLinkNext = nullptr;

        AddCppProperty(Property);

        const uint32 PropertyValueOffset = Component->SetScratchSpaceValues(Values);
        AssignPropertyOffset(Property, PropertyValueOffset);

        {
            FString PropertyLabel = UTF8_TO_TCHAR(Label.c_str());
            Property->SetMetaData(TEXT("DisplayName"), *PropertyLabel);
        }

        Property->SetMetaData(TEXT("EditAnywhere"), TEXT("1"));
        Property->SetMetaData(TEXT("BlueprintReadOnly"), TEXT("1"));
        Property->SetMetaData(TEXT("Category"), TEXT("HoudiniProperties"));

        const PRM_Range* Range = Template->getRangePtr();
        if(Range)
        {
            if(Range->hasParmMin())
            {
                const float ParmMin = (float) Range->getParmMin();
                Property->SetMetaData(TEXT("ClampMin"), *FString::SanitizeFloat(ParmMin));
            }

            if(Range->hasParmMax())
            {
                const float ParmMax = (float) Range->getParmMax();
                Property->SetMetaData(TEXT("ClampMax"), *FString::SanitizeFloat(ParmMax));
            }

            if(Range->hasUIMin())
            {
                const float UIMin = (float) Range->getUIMin();
                Property->SetMetaData(TEXT("UIMin"), *FString::SanitizeFloat(UIMin));
            }

            if(Range->hasUIMax())
            {
                const float UIMax = (float) Range->getUIMax();
                Property->SetMetaData(TEXT("UIMax"), *FString::SanitizeFloat(UIMax));
            }
        }
    }

    return Property;
}


template <typename TPropertyType, typename TType>
TPropertyType*
UHoudiniNodeClass::CreateParameterCommon(const PRM_Template* Template, TType Value)
{
    TArray<TType> Values;
    Values.Add(Value);

    TPropertyType* Property = CreateParameterCommon<TPropertyType>(Template, Values);
    return Property;
}

