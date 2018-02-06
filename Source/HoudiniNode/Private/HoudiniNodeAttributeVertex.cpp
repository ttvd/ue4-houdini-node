#include "HoudiniNodeAttributeVertex.h"
#include "HoudiniNodePrivatePCH.h"

#pragma warning(push)
#pragma warning(disable : 4706)


FHoudiniNodeAttributeVertex::FHoudiniNodeAttributeVertex(const FHoudiniNodeDetail& InDetail, const FString& InName) :
    FHoudiniNodeAttribute(InDetail, InName, GA_ATTRIB_VERTEX)
{

}


bool
FHoudiniNodeAttributeVertex::Get(const TArray<GA_Primitive*>& Primitives, bool bScale, TArray<FVector>& Values) const
{
    Values.Empty();

    if(!IsValid())
    {
        return false;
    }

    GA_RWHandleV3 AttributeHandle = FindAttributeHandle<GA_RWHandleV3>(3);
    if(!AttributeHandle.isValid())
    {
        return false;
    }

    TArray<GA_Offset> VertexOffsets;
    if(!Detail.GetPrimitiveVertices(Primitives, VertexOffsets))
    {
        return false;
    }

    const float Scale = Detail.GetScale();

    for(int32 Idx = 0; Idx < VertexOffsets.Num(); ++Idx)
    {
        GA_Offset VertexOffset = VertexOffsets[Idx];

        if(VertexOffset == GA_INVALID_OFFSET)
        {
            continue;
        }

        const UT_Vector3& AttributeValue = AttributeHandle.get(VertexOffset);

        FVector Value(AttributeValue.x(), AttributeValue.y(), AttributeValue.z());
        Swap(Value.Y, Value.Z);

        if(bScale)
        {
            Value *= Scale;
        }

        Values.Add(Value);
    }

    return true;
}


bool
FHoudiniNodeAttributeVertex::Get(const TArray<GA_Primitive*>& Primitives, TArray<FLinearColor>& Values) const
{
    Values.Empty();

    if(!IsValid())
    {
        return false;
    }

    const float Scale = Detail.GetScale();
    bool bSuccess = false;

    TArray<GA_Offset> VertexOffsets;
    if(!Detail.GetPrimitiveVertices(Primitives, VertexOffsets))
    {
        return false;
    }

    {
        GA_RWHandleV3 AttributeHandle = FindAttributeHandle<GA_RWHandleV3>(3);
        if(AttributeHandle.isValid())
        {
            for(int32 Idx = 0; Idx < VertexOffsets.Num(); ++Idx)
            {
                GA_Offset VertexOffset = VertexOffsets[Idx];

                if(VertexOffset == GA_INVALID_OFFSET)
                {
                    continue;
                }

                const UT_Vector3& AttributeValue = AttributeHandle.get(VertexOffset);

                FLinearColor Value(AttributeValue.x(), AttributeValue.y(), AttributeValue.z());
                Values.Add(Value);
            }

            bSuccess = true;
        }
    }

    if(!bSuccess)
    {
        GA_RWHandleV4 AttributeHandle = FindAttributeHandle<GA_RWHandleV4>(4);
        if(AttributeHandle.isValid())
        {
            for(int32 Idx = 0; Idx < VertexOffsets.Num(); ++Idx)
            {
                GA_Offset VertexOffset = VertexOffsets[Idx];

                if(VertexOffset == GA_INVALID_OFFSET)
                {
                    continue;
                }

                const UT_Vector4& AttributeValue = AttributeHandle.get(VertexOffset);

                FLinearColor Value(AttributeValue.x(), AttributeValue.y(), AttributeValue.z(), AttributeValue.w());
                Values.Add(Value);
            }
        }
    }

    return Values.Num() > 0;
}


bool
FHoudiniNodeAttributeVertex::Get(const TArray<GA_Primitive*>& Primitives, TArray<FColor>& Values) const
{
    Values.Empty();

    TArray<FLinearColor> LinearColors;
    if(!Get(Primitives, LinearColors))
    {
        return false;
    }

    for(int32 Idx = 0; Idx < LinearColors.Num(); ++Idx)
    {
        const FLinearColor& LinearColor = LinearColors[Idx];
        const FColor& Color = LinearColor.ToFColor(false);

        Values.Add(Color);
    }

    return Values.Num() > 0;
}

#pragma warning(pop)
