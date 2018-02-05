#include "HoudiniNodeAttributeVertex.h"
#include "HoudiniNodePrivatePCH.h"

#pragma warning(push)
#pragma warning(disable : 4706)


FHoudiniNodeAttributeVertex::FHoudiniNodeAttributeVertex(const FHoudiniNodeDetail& InDetail, const FString& InName) :
    FHoudiniNodeAttribute(InDetail, InName, GA_ATTRIB_VERTEX)
{

}

#pragma warning(pop)
