#include "HoudiniNodeAttributeVertex.h"
#include "HoudiniNodePrivatePCH.h"

#pragma warning(push)
#pragma warning(disable : 4706)


FHoudiniNodeAttributeVertex::FHoudiniNodeAttributeVertex(const FHoudiniNodeDetail& InDetail, const FString& InName) :
    FHoudiniNodeAttribute(InDetail, InName, GA_ATTRIB_VERTEX)
{

}


bool
FHoudiniNodeAttributeVertex::Get(const TArray<GA_Primitive*>& Primitives, TArray<FVector>& Values) const
{
    Values.Empty();

    if(!IsValid())
    {
        return false;
    }



    return true;
}


#pragma warning(pop)
