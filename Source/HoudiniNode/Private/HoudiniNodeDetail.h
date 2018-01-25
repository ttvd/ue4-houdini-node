#pragma once


class OBJ_Node;
class GU_Detail;
class GA_Primitive;


class HOUDININODE_API FHoudiniNodeDetail
{
public:

    //! Create detail from a given object node.
    FHoudiniNodeDetail(OBJ_Node* InNode);

public:

    //! Cook this detail at a given time.
    bool Cook(float Time);

    //! Return true if this is a valid detail.
    bool IsValid() const;

public:

    //! Retrieve all primitives of this detail.
    bool GetAllPrimitives(TArray<GA_Primitive*>& Primitives) const;

protected:

    //! Corresponding Houdini object node this detail is constructed from.
    OBJ_Node* Node;

    //! Corresponding Houdini detail.
    GU_Detail* Detail;
};
