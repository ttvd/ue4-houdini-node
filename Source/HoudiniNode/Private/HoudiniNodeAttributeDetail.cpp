#include "HoudiniNodeAttributeDetail.h"
#include "HoudiniNodePrivatePCH.h"

#pragma warning(push)
#pragma warning(disable : 4706)


FHoudiniNodeAttributeDetail::FHoudiniNodeAttributeDetail(const FHoudiniNodeDetail& InDetail, const FString& InName) :
    FHoudiniNodeAttribute(InDetail, InName, GA_ATTRIB_GLOBAL)
{

}

#pragma warning(pop)
