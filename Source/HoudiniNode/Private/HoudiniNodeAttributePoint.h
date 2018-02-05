#pragma once
#include "HoudiniNodeAttribute.h"


class GA_Primitive;
class UObject;


class HOUDININODE_API FHoudiniNodeAttributePoint : public FHoudiniNodeAttribute
{
public:

    //! Create a point attribute object for a given detail with a given name.
    FHoudiniNodeAttributePoint(const FHoudiniNodeDetail& InDetail, const FString& InName);

public:

    //! Get positions for all points.
    bool GetAllPositions(TArray<FVector>& Positions) const;

    //! Get positions for given points.
    bool GetPositions(const TArray<GA_Offset>& Points, TArray<FVector>& Positions) const;

};

