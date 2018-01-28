#include "HoudiniNodeAttributePoint.h"
#include "HoudiniNodePrivatePCH.h"

#pragma warning(push)
#pragma warning(disable : 4706)


FHoudiniNodeAttributePoint::FHoudiniNodeAttributePoint(GU_Detail* InDetail, const FString& InName) :
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

    GA_FOR_ALL_PTOFF(Detail, PointOffset)
    {
        if(PointOffset == GA_INVALID_OFFSET)
        {
            continue;
        }

        const UT_Vector3& Position = Detail->getPos3(PointOffset);
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

    for(int32 Idx = 0; Idx < Points.Num(); ++Idx)
    {
        GA_Offset PointOffset = Points[Idx];

        if(PointOffset == GA_INVALID_OFFSET)
        {
            continue;
        }

        const UT_Vector3& Position = Detail->getPos3(PointOffset);
        FVector PointPosition(Position.x(), Position.z(), Position.y());
        PointPosition *= 100.0f;

        Positions.Add(PointPosition);
    }

    return Positions.Num() > 0;
}

#pragma warning(pop)
