#pragma once

#include "HoudiniNodePropertyType.h"

class PRM_Template;

class UProperty;
class UHoudiniNodeComponent;


class HOUDININODE_API FHoudiniNodePropertyCommon
{
public:

    FHoudiniNodePropertyCommon();
    virtual ~FHoudiniNodePropertyCommon();

    friend class UHoudiniNodeClass;

public:

    //! Retrieve property offset.
    uint32 GetPropertyOffset() const;

    //! Retrieve property size.
    uint32 GetPropertyDim() const;

    //! Return property type.
    EHoudiniNodePropertyType::Enum GetPropertyType() const;

protected:

    //! Initialize the property.
    void InitializeProperty(UProperty* InProperty, UHoudiniNodeComponent* InComponent, const PRM_Template* InTemplate,
        EHoudiniNodePropertyType::Enum InPropertyType);

    //! Construct the property.
    template <typename TType> bool ConstructProperty(bool bAssign, bool bComputeOffset);

    //! Assign this property to a class.
    void AssignClass();

protected:

    //! Assign property metadata.
    void AssignPropertyMeta() const;

    //! Assign property ranges.
    void AssignPropertyRanges() const;

protected:

    //! Retrieve float values for a given property.
    bool GetValues(UHoudiniNodeComponent* Component, bool bAssign, bool bComputeOffset,
        TArray<float>& Values) const;

    //! Retrieve integer values for a given property.
    bool GetValues(UHoudiniNodeComponent* Component, bool bAssign, bool bComputeOffset,
        TArray<int32>& Values) const;

    //! Retrieve string values for a given property.
    bool GetValues(UHoudiniNodeComponent* Component, bool bAssign, bool bComputeOffset,
        TArray<FString>& Values) const;

protected:

    //! Set values for a given property.
    bool UploadValues() const;

protected:

    //! Assign property offset.
    void AssignPropertyOffset(uint32 Offset) const;

protected:

    //! Retrieve current node.
    OP_Node* GetNode() const;

    //! Retrieve current time.
    float GetCookTime() const;

protected:

    //! Property that is being constructed.
    UProperty* Property;

    //! Corresponding data component.
    UHoudiniNodeComponent* Component;

    //! Template used to construct the property.
    PRM_Template* Template;

    //! Type of this property.
    EHoudiniNodePropertyType::Enum PropertyType;
};


template <typename TType>
bool
FHoudiniNodePropertyCommon::ConstructProperty(bool bAssign, bool bComputeOffset)
{
    if(Component)
    {
        return false;
    }

    AssignPropertyMeta();
    AssignPropertyRanges();

    TArray<TType> Values;
    if(!GetValues(Component, bAssign, bComputeOffset, Values))
    {
        return false;
    }

    return true;
}


