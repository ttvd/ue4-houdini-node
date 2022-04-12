#include "HoudiniNodeAttributePoint.h"
#include "HoudiniNodePrivatePCH.h"

#pragma warning(push)
#pragma warning(disable : 4706)


FHoudiniNodeAttributePoint::FHoudiniNodeAttributePoint(const FHoudiniNodeDetail& InDetail, const FString& InName) :
    FHoudiniNodeAttribute(InDetail, InName, GA_ATTRIB_POINT)
{

}


bool
FHoudiniNodeAttributePoint::GetAllPositions(TArray<FVector>& Positions) const
{
    Positions.Empty();

    if(!IsValid())
    {
        return false;
    }

    GA_Offset PointOffset = GA_INVALID_OFFSET;

    GU_Detail* DetailPtr = Detail.GetDetail();
    GA_FOR_ALL_PTOFF(DetailPtr, PointOffset)
    {
        if(PointOffset == GA_INVALID_OFFSET)
        {
            continue;
        }

        const UT_Vector3& Position = DetailPtr->getPos3(PointOffset);
        FVector PointPosition(Position.x(), Position.z(), Position.y());
        PointPosition *= 100.0f;

        Positions.Add(PointPosition);
    }

    return Positions.Num() > 0;
}


bool
FHoudiniNodeAttributePoint::GetPositions(const TArray<GA_Offset>& Points, TArray<FVector>& Positions) const
{
    Positions.Empty();

    if(!IsValid())
    {
        return false;
    }

    GU_Detail* DetailPtr = Detail.GetDetail();

    for(int32 Idx = 0; Idx < Points.Num(); ++Idx)
    {
        GA_Offset PointOffset = Points[Idx];

        if(PointOffset == GA_INVALID_OFFSET)
        {
            continue;
        }

        const UT_Vector3& Position = DetailPtr->getPos3(PointOffset);
        FVector PointPosition(Position.x(), Position.z(), Position.y());
        PointPosition *= 100.0f;

        Positions.Add(PointPosition);
    }

    return Positions.Num() > 0;
}

#pragma warning(pop)
