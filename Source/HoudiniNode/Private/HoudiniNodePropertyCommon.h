#pragma once


class OP_Node;
class PRM_Template;

class UProperty;
class UHoudiniNodeComponent;


class HOUDININODE_API FHoudiniNodePropertyCommon
{
public:

    FHoudiniNodePropertyCommon();
    virtual ~FHoudiniNodePropertyCommon();

protected:

    //! Initialize the property.
    void InitializeProperty(UProperty* InProperty, UHoudiniNodeComponent* InComponent, const PRM_Template* InTemplate);

    //! Construct the property.
    template <typename TType> bool ConstructProperty(OP_Node* Node, float Time);

protected:

    //! Assign property metadata.
    void AssignPropertyMeta() const;

    //! Assign property ranges.
    void AssignPropertyRanges() const;

protected:

    //! Retrieve float values for a given property.
    bool GetPropertyValues(OP_Node* Node, UHoudiniNodeComponent* Component, float Time, bool bAssign, TArray<float>& Values) const;

    //! Retrieve float integer for a given property.
    bool GetPropertyValues(OP_Node* Node, UHoudiniNodeComponent* Component, float Time, bool bAssign, TArray<int32>& Values) const;

private:

    //! Assign property offset.
    void AssignPropertyOffset(uint32 Offset) const;

protected:

    //! Property that is being constructed.
    UProperty* Property;

    //! Corresponding data component.
    UHoudiniNodeComponent* Component;

    //! Template used to construct the property.
    PRM_Template* Template;
};


template <typename TType>
bool
FHoudiniNodePropertyCommon::ConstructProperty(OP_Node* Node, float Time)
{
    if(!Node || !Component)
    {
        return false;
    }

    AssignPropertyMeta();
    AssignPropertyRanges();

    TArray<TType> Values;
    if(!GetPropertyValues(Node, Component, Time, true, Values))
    {
        return false;
    }

    return true;
}

