#pragma once
#include "HoudiniNodeAttribute.h"


class GA_Primitive;
class UObject;


class HOUDININODE_API FHoudiniNodeAttributeDetail : public FHoudiniNodeAttribute
{
public:

    //! Create a detail attribute object for a given detail with a given name.
    FHoudiniNodeAttributeDetail(const FHoudiniNodeDetail& InDetail, const FString& InName);

public:

};

