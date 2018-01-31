#pragma once


class OBJ_Node;
class GU_Detail;
class GA_Primitive;


class HOUDININODE_API FHoudiniNodeDetail
{
public:

    //! Create detail from a given object node.
    FHoudiniNodeDetail(OBJ_Node* InNode);

    //! Destructor (resets the locks).
    ~FHoudiniNodeDetail();

public:

    //! Cook this detail at a given time.
    bool Cook(float Time);

    //! Return true if this is a valid detail.
    bool IsValid() const;

public:

    //! Retrieve all primitives of this detail.
    bool GetAllPrimitives(TArray<GA_Primitive*>& Primitives) const;

    //! Retrieve all points of this detail.
    bool GetAllPoints(TArray<GA_Offset>& Points) const;

public:

    //! Get all parts.
    bool GetParts(TMap<int32, TArray<GA_Primitive*> >& Parts) const;

protected:

    //! Reset this detail (release locks).
    void Reset();

protected:

    //! Corresponding Houdini detail handle.
    GU_DetailHandle DetailHandle;

    //! Corresponding Houdini object node this detail is constructed from.
    OBJ_Node* Node;

    //! Corresponding Houdini detail of the active display node.
    GU_Detail* Detail;
};
