#include "HoudiniNodeAttributeCast.h"
#include "HoudiniNodeAttributePoint.h"
#include "HoudiniNodeAttributeVertex.h"
#include "HoudiniNodeAttributePrimitive.h"
#include "HoudiniNodeAttributeDetail.h"
#include "HoudiniNodePrivatePCH.h"

#pragma warning(push)
#pragma warning(disable : 4706)


FHoudiniNodeAttributeCast::FHoudiniNodeAttributeCast(const FHoudiniNodeDetail& InDetail, const FString& InName) :
    Detail(InDetail),
    Name(InName),
    NameRaw("")
{
    std::string RawString = TCHAR_TO_UTF8(*InName);
    NameRaw = UT_String(RawString);
}


bool
FHoudiniNodeAttributeCast::IsValid() const
{
    if(Detail.IsValid())
    {
        return true;
    }

    return false;
}


bool
FHoudiniNodeAttributeCast::GetAsVertex(const TArray<GA_Primitive*>& Primitives, bool bScale, TArray<FVector>& Values) const
{
    {
        FHoudiniNodeAttributeVertex Attribute(Detail, Name);
        if(Attribute.Exists())
        {
        
        }
    }

    {
        FHoudiniNodeAttributePoint Attribute(Detail, Name);
        if(Attribute.Exists())
        {
        
        }
    }

    {
        FHoudiniNodeAttributePrimitive Attribute(Detail, Name);
        if(Attribute.Exists())
        {
            TArray<FVector> Vectors;
            if(Attribute.Get(Primitives, bScale, Vectors))
            {
                for(int32 Idx = 0; Idx < Primitives.Num(); ++Idx)
                {
                    GA_Primitive* Prim = Primitives[Idx];
                    if(Prim)
                    {
                        const FVector& Value = Vectors[Idx];
                        const int32 VertexCount = Prim->getVertexCount();

                        for(int32 Idv = 0; Idv < VertexCount; ++Idv)
                        {
                            Values.Add(Value);
                        }
                    }
                }

                return true;
            }
        }
    }

    {
        FHoudiniNodeAttributeDetail Attribute(Detail, Name);
        if(Attribute.Exists())
        {
        
        }
    }

    return true;
}

#pragma warning(pop)
