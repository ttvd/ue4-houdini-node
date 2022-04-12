#pragma once


class GA_Primitive;
class FHoudiniNodeDetail;


class HOUDININODE_API FHoudiniNodePrimitive
{
public:

    //! Create a primitive wrapper.
    FHoudiniNodePrimitive(const FHoudiniNodeDetail& InDetail, GA_Primitive* InPrimitive);

public:

    //! Return true if this is a valid primitive.
    bool IsValid() const;

public:

    //! Return number of vertices in this primitive.
    int32 GetVertexCount() const;

protected:

    //! Return vertex offsets for this primitive.
    bool GetVertexOffsets(TArray<GA_Offset>& VertexOffsets) const;

    //! Return point offsets for this primitive.
    bool GetPointOffsets(TArray<GA_Offset>& PointOffsets) const;

    //! Return point positions of this primitive.
    bool GetPointPositions(TArray<FVector>& PointPositions) const;

protected:

    //! Detail.
    const FHoudiniNodeDetail& Detail;

    //! Primitive.
    GA_Primitive* Primitive;
};
