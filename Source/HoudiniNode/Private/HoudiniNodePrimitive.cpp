#include "HoudiniNodePrimitive.h"
#include "HoudiniNodeDetail.h"
#include "HoudiniNodePrivatePCH.h"

#pragma warning(push)
#pragma warning(disable : 4706)


FHoudiniNodePrimitive::FHoudiniNodePrimitive(const FHoudiniNodeDetail& InDetail, GA_Primitive* InPrimitive) :
    Detail(InDetail),
    Primitive(InPrimitive)
{

}


bool
FHoudiniNodePrimitive::IsValid() const
{
    if(!Detail.IsValid())
    {
        return false;
    }

    if(!Primitive)
    {
        return false;
    }

    return true;
}


int32
FHoudiniNodePrimitive::GetVertexCount() const
{
    if(!IsValid())
    {
        return 0;
    }

    return Primitive->getVertexCount();
}


bool
FHoudiniNodePrimitive::GetVertexOffsets(TArray<GA_Offset>& VertexOffsets) const
{
    VertexOffsets.Empty();

    if(!IsValid())
    {
        return false;
    }

    const int32 VertexCount = Primitive->getVertexCount();
    for(int32 Idx = 0; Idx < VertexCount; ++Idx)
    {
        GA_Offset VertexOffset = Primitive->getVertexOffset(Idx);
        VertexOffsets.Add(VertexOffset);
    }

    return VertexOffsets.Num() > 0;
}


bool
FHoudiniNodePrimitive::GetPointOffsets(TArray<GA_Offset>& PointOffsets) const
{
    PointOffsets.Empty();

    if(!IsValid())
    {
        return false;
    }

    const int32 VertexCount = Primitive->getVertexCount();
    for(int32 Idx = 0; Idx < VertexCount; ++Idx)
    {
        GA_Offset PointOffset = Primitive->getPointOffset(Idx);
        PointOffsets.Add(PointOffset);
    }

    return PointOffsets.Num() > 0;
}


bool
FHoudiniNodePrimitive::GetPointPositions(TArray<FVector>& PointPositions) const
{
    PointPositions.Empty();

    if(!IsValid())
    {
        return false;
    }

    GU_Detail* DetailRaw = Detail.GetDetail();

    const int32 VertexCount = Primitive->getVertexCount();
    for(int32 Idx = 0; Idx < VertexCount; ++Idx)
    {
        GA_Offset PointOffset = Primitive->getPointOffset(Idx);
        const UT_Vector3& PointRaw = DetailRaw->getPos3(PointOffset);

        FVector PointPosition(PointRaw.x(), PointRaw.z(), PointRaw.y());
        PointPosition *= Scale;

        PointPositions.Add(PointPosition);
    }

    return PointPositions.Num() > 0;
}

#pragma warning(pop)
