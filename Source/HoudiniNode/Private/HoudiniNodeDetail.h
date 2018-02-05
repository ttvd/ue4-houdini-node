#pragma once


class GU_Detail;
class GA_Primitive;
class GA_Attribute;
class SOP_Node;


class HOUDININODE_API FHoudiniNodeDetail
{
public:

    FHoudiniNodeDetail(SOP_Node* InNode, float InScale = 100.0f);
    ~FHoudiniNodeDetail();

public:

    //! Return true if this is a valid detail.
    bool IsValid() const;

public:

    //! Cook this detail.
    bool Cook(float InTime);

public:

    //! Return number of primitives in this detail.
    int32 GetPrimitiveCount() const;

public:

    //! Retrieve all points of this detail.
    bool GetAllPoints(TArray<GA_Offset>& Points) const;
    bool GetAllPoints(TArray<uint32>& Points) const;

    //! Given a list of primitives, return the corresponding list of points.
    bool GetPrimitivePoints(const TArray<GA_Primitive*>& Primitives, TArray<GA_Offset>& Points) const;
    bool GetPrimitivePoints(const TArray<GA_Primitive*>& Primitives, TArray<uint32>& Points) const;

public:

    //! Get positions for all points.
    bool GetAllPointPositions(TArray<FVector>& Positions) const;

    //! Get positions for specified points.
    bool GetPointPositions(const TArray<GA_Offset>& Points, TArray<FVector>& Positions) const;

    //! Get positions for points of specified primitives.
    bool GetPrimitivePointPositions(const TArray<GA_Primitive*>& Primitives, TArray<FVector>& Positions) const;

public:

    //! Retrieve all primitives of this detail.
    bool GetAllPrimitives(TArray<GA_Primitive*>& Primitives) const;

    //! Retrieve all primitives that are members of a given group.
    bool GetGroupPrimitives(const FString& GroupName, TArray<GA_Primitive*>& Primitives) const;

public:

    //! Get parts grouped by the generator name.
    bool GetPartPrims(TMap<FString, TMap<int32, TArray<GA_Primitive*> > >& Parts) const;

    //! Get points grouped by the generator name.
    bool GetPartPoints(TMap<FString, TMap<int32, TArray<GA_Offset> > >& Parts) const;

public:

    //! Locate an attribute.
    GA_Attribute* FindAttribute(const FString& AttributeName, GA_AttributeOwner Owner) const;
    GA_Attribute* FindAttribute(const UT_String& AttributeName, GA_AttributeOwner Owner) const;

public:

    //! Return the underlying detail.
    GU_Detail* GetDetail() const;

protected:

    //! Corresponding Houdini detail handle.
    GU_DetailHandle DetailHandle;

    //! SOP node.
    SOP_Node* Node;

    //! Stored detail.
    GU_Detail* Detail;

    //! Time of cooking.
    float Time;

    //! Scale.
    float Scale;
};
