#include "HoudiniNodeAttributePrimitive.h"
#include "HoudiniNodePrivatePCH.h"

#pragma warning(push)
#pragma warning(disable : 4706)


FHoudiniNodeAttributePrimitive::FHoudiniNodeAttributePrimitive(const FHoudiniNodeDetail& InDetail, const FString& InName) :
    FHoudiniNodeAttribute(InDetail, InName, GA_ATTRIB_PRIMITIVE)
{

}


bool
FHoudiniNodeAttributePrimitive::SelectNonZero(TArray<GA_Primitive*>& Prims) const
{
    Prims.Empty();

    if(!IsValid())
    {
        return false;
    }

    GA_RWHandleI AttributeHandle = FindAttributeHandle<GA_RWHandleI>(1);
    if(!AttributeHandle.isValid())
    {
        return false;
    }

    GU_Detail* DetailPtr = Detail.GetDetail();
    GA_Primitive* Prim = nullptr;

    GA_FOR_ALL_PRIMITIVES(DetailPtr, Prim)
    {
        if(!Prim)
        {
            continue;
        }

        const GA_Offset PrimOffset = Prim->getMapOffset();
        const int32 AttributeValue = AttributeHandle.get(PrimOffset);

        if(AttributeValue > 0)
        {
            Prims.Add(Prim);
        }
    }

    return Prims.Num() > 0;
}


bool
FHoudiniNodeAttributePrimitive::Select(int32 Value, TArray<GA_Primitive*>& Prims) const
{
    Prims.Empty();

    if(!IsValid())
    {
        return false;
    }

    GA_RWHandleI AttributeHandle = FindAttributeHandle<GA_RWHandleI>(1);
    if(!AttributeHandle.isValid())
    {
        return false;
    }

    GU_Detail* DetailPtr = Detail.GetDetail();
    GA_Primitive* Prim = nullptr;

    GA_FOR_ALL_PRIMITIVES(DetailPtr, Prim)
    {
        if(!Prim)
        {
            continue;
        }

        const GA_Offset PrimOffset = Prim->getMapOffset();
        const int32 AttributeValue = AttributeHandle.get(PrimOffset);

        if(Value == AttributeValue)
        {
            Prims.Add(Prim);
        }
    }

    return Prims.Num() > 0;
}


bool
FHoudiniNodeAttributePrimitive::Select(const FString& Value, TArray<GA_Primitive*>& Prims) const
{
    Prims.Empty();

    if(!IsValid())
    {
        return false;
    }

    GA_RWHandleS AttributeHandle = FindAttributeHandle<GA_RWHandleS>(1);
    if(!AttributeHandle.isValid())
    {
        return false;
    }

    std::string RawString = TCHAR_TO_UTF8(*Value);
    UT_String RawValue(RawString);

    GU_Detail* DetailPtr = Detail.GetDetail();
    GA_Primitive* Prim = nullptr;

    GA_FOR_ALL_PRIMITIVES(DetailPtr, Prim)
    {
        if(!Prim)
        {
            continue;
        }

        const GA_Offset PrimOffset = Prim->getMapOffset();
        UT_String AttributeValue = "";
        AttributeValue = AttributeHandle.get(PrimOffset);

        if(AttributeValue.equal(RawValue, false))
        {
            Prims.Add(Prim);
        }
    }

    return Prims.Num() > 0;
}


bool
FHoudiniNodeAttributePrimitive::Select(UObject* Object, TArray<GA_Primitive*>& Prims) const
{
    Prims.Empty();

    if(!IsValid())
    {
        return false;
    }

    FString ObjectPath(TEXT(""));

    if(Object)
    {
        ObjectPath = Object->GetPathName();
    }

    return Select(ObjectPath, Prims);
}


bool
FHoudiniNodeAttributePrimitive::Group(const TArray<GA_Primitive*>& Input, TMap<int32, TArray<GA_Primitive*> >& Prims) const
{
    Prims.Empty();

    if(!IsValid())
    {
        return false;
    }

    GA_RWHandleI AttributeHandle = FindAttributeHandle<GA_RWHandleI>(1);
    if(!AttributeHandle.isValid())
    {
        return false;
    }

    for(int32 Idx = 0; Idx < Input.Num(); ++Idx)
    {
        GA_Primitive* Prim = nullptr;
        if(!Prim)
        {
            continue;
        }

        const GA_Offset PrimOffset = Prim->getMapOffset();
        const int32 AttributeValue = AttributeHandle.get(PrimOffset);

        TArray<GA_Primitive*>* FoundPrimArray = Prims.Find(AttributeValue);
        if(FoundPrimArray)
        {
            TArray<GA_Primitive*>& PrimArray = *FoundPrimArray;
            PrimArray.Add(Prim);
        }
        else
        {
            TArray<GA_Primitive*> PrimArray;
            PrimArray.Add(Prim);

            Prims.Add(AttributeValue, PrimArray);
        }
    }

    return Prims.Num() > 0;
}


bool
FHoudiniNodeAttributePrimitive::Group(TMap<int32, TArray<GA_Primitive*> >& Prims) const
{
    Prims.Empty();

    if(!IsValid())
    {
        return false;
    }

    GA_RWHandleI AttributeHandle = FindAttributeHandle<GA_RWHandleI>(1);
    if(!AttributeHandle.isValid())
    {
        return false;
    }

    GU_Detail* DetailPtr = Detail.GetDetail();
    GA_Primitive* Prim = nullptr;

    GA_FOR_ALL_PRIMITIVES(DetailPtr, Prim)
    {
        if(!Prim)
        {
            continue;
        }

        const GA_Offset PrimOffset = Prim->getMapOffset();
        const int32 AttributeValue = AttributeHandle.get(PrimOffset);

        TArray<GA_Primitive*>* FoundPrimArray = Prims.Find(AttributeValue);
        if(FoundPrimArray)
        {
            TArray<GA_Primitive*>& PrimArray = *FoundPrimArray;
            PrimArray.Add(Prim);
        }
        else
        {
            TArray<GA_Primitive*> PrimArray;
            PrimArray.Add(Prim);

            Prims.Add(AttributeValue, PrimArray);
        }
    }

    return Prims.Num() > 0;
}


bool
FHoudiniNodeAttributePrimitive::Group(TMap<FString, TArray<GA_Primitive*> >& Prims) const
{
    Prims.Empty();

    if(!IsValid())
    {
        return false;
    }

    GA_RWHandleS AttributeHandle = FindAttributeHandle<GA_RWHandleS>(1);
    if(!AttributeHandle.isValid())
    {
        return false;
    }

    GU_Detail* DetailPtr = Detail.GetDetail();
    GA_Primitive* Prim = nullptr;

    GA_FOR_ALL_PRIMITIVES(DetailPtr, Prim)
    {
        if(!Prim)
        {
            continue;
        }

        const GA_Offset PrimOffset = Prim->getMapOffset();
        UT_String AttributeValueRaw;
        AttributeValueRaw = AttributeHandle.get(PrimOffset);
        FString AttributeValue = UTF8_TO_TCHAR(AttributeValueRaw.c_str());

        TArray<GA_Primitive*>* FoundPrimArray = Prims.Find(AttributeValue);
        if(FoundPrimArray)
        {
            TArray<GA_Primitive*>& PrimArray = *FoundPrimArray;
            PrimArray.Add(Prim);
        }
        else
        {
            TArray<GA_Primitive*> PrimArray;
            PrimArray.Add(Prim);

            Prims.Add(AttributeValue, PrimArray);
        }
    }

    return Prims.Num() > 0;
}


bool
FHoudiniNodeAttributePrimitive::Group(const TArray<GA_Primitive*>& Input, TMap<FString, TArray<GA_Primitive*> >& Prims) const
{
    Prims.Empty();

    if(!IsValid())
    {
        return false;
    }

    GA_RWHandleS AttributeHandle = FindAttributeHandle<GA_RWHandleS>(1);
    if(!AttributeHandle.isValid())
    {
        return false;
    }

    for(int32 Idx = 0; Idx < Input.Num(); ++Idx)
    {
        GA_Primitive* Prim = nullptr;
        if(!Prim)
        {
            continue;
        }

        const GA_Offset PrimOffset = Prim->getMapOffset();
        UT_String AttributeValueRaw;
        AttributeValueRaw = AttributeHandle.get(PrimOffset);
        FString AttributeValue = UTF8_TO_TCHAR(AttributeValueRaw.c_str());

        TArray<GA_Primitive*>* FoundPrimArray = Prims.Find(AttributeValue);
        if(FoundPrimArray)
        {
            TArray<GA_Primitive*>& PrimArray = *FoundPrimArray;
            PrimArray.Add(Prim);
        }
        else
        {
            TArray<GA_Primitive*> PrimArray;
            PrimArray.Add(Prim);

            Prims.Add(AttributeValue, PrimArray);
        }
    }

    return Prims.Num() > 0;
}


bool
FHoudiniNodeAttributePrimitive::Group(TMap<UObject*, TArray<GA_Primitive*> >& Prims) const
{
    Prims.Empty();

    if(!IsValid())
    {
        return false;
    }

    GA_RWHandleS AttributeHandle = FindAttributeHandle<GA_RWHandleS>(1);
    if(!AttributeHandle.isValid())
    {
        return false;
    }

    GU_Detail* DetailPtr = Detail.GetDetail();
    GA_Primitive* Prim = nullptr;

    GA_FOR_ALL_PRIMITIVES(DetailPtr, Prim)
    {
        if(!Prim)
        {
            continue;
        }

        const GA_Offset PrimOffset = Prim->getMapOffset();
        UT_String AttributeValueRaw;
        AttributeValueRaw = AttributeHandle.get(PrimOffset);
        FString AttributeValue = UTF8_TO_TCHAR(AttributeValueRaw.c_str());

        UObject* FoundObject = nullptr;
        if(!AttributeValue.IsEmpty())
        {
            FoundObject = StaticLoadObject(UObject::StaticClass(), nullptr, *AttributeValue, nullptr,
                LOAD_None, nullptr);
        }

        TArray<GA_Primitive*>* FoundPrimArray = Prims.Find(FoundObject);
        if(FoundPrimArray)
        {
            TArray<GA_Primitive*>& PrimArray = *FoundPrimArray;
            PrimArray.Add(Prim);
        }
        else
        {
            TArray<GA_Primitive*> PrimArray;
            PrimArray.Add(Prim);

            Prims.Add(FoundObject, PrimArray);
        }
    }

    return Prims.Num() > 0;
}


bool
FHoudiniNodeAttributePrimitive::Group(const TArray<GA_Primitive*>& Input, TMap<UObject*, TArray<GA_Primitive*> >& Prims) const
{
    Prims.Empty();

    if(!IsValid())
    {
        return false;
    }

    GA_RWHandleS AttributeHandle = FindAttributeHandle<GA_RWHandleS>(1);
    if(!AttributeHandle.isValid())
    {
        return false;
    }

    for(int32 Idx = 0; Idx < Input.Num(); ++Idx)
    {
        GA_Primitive* Prim = nullptr;
        if(!Prim)
        {
            continue;
        }

        const GA_Offset PrimOffset = Prim->getMapOffset();
        UT_String AttributeValueRaw;
        AttributeValueRaw = AttributeHandle.get(PrimOffset);
        FString AttributeValue = UTF8_TO_TCHAR(AttributeValueRaw.c_str());

        UObject* FoundObject = nullptr;
        if(!AttributeValue.IsEmpty())
        {
            FoundObject = StaticLoadObject(UObject::StaticClass(), nullptr, *AttributeValue, nullptr,
                LOAD_None, nullptr);
        }

        TArray<GA_Primitive*>* FoundPrimArray = Prims.Find(FoundObject);
        if(FoundPrimArray)
        {
            TArray<GA_Primitive*>& PrimArray = *FoundPrimArray;
            PrimArray.Add(Prim);
        }
        else
        {
            TArray<GA_Primitive*> PrimArray;
            PrimArray.Add(Prim);

            Prims.Add(FoundObject, PrimArray);
        }
    }

    return Prims.Num() > 0;
}


bool
FHoudiniNodeAttributePrimitive::Get(const TArray<GA_Primitive*>& Prims, TArray<int32>& Values) const
{
    Values.Empty();

    if(!IsValid())
    {
        return false;
    }

    GA_RWHandleI AttributeHandle = FindAttributeHandle<GA_RWHandleI>(1);
    if(!AttributeHandle.isValid())
    {
        return false;
    }

    for(int32 Idx = 0; Idx < Prims.Num(); ++Idx)
    {
        GA_Primitive* Prim = Prims[Idx];
        if(!Prim)
        {
            continue;
        }

        const GA_Offset PrimOffset = Prim->getMapOffset();
        const int32 AttributeValue = AttributeHandle.get(PrimOffset);

        Values.Add(AttributeValue);
    }

    return Values.Num() > 0;
}


bool
FHoudiniNodeAttributePrimitive::Get(const TArray<GA_Primitive*>& Prims, TArray<FString>& Values) const
{
    Values.Empty();

    if(!IsValid())
    {
        return false;
    }

    GA_RWHandleS AttributeHandle = FindAttributeHandle<GA_RWHandleS>(1);
    if(!AttributeHandle.isValid())
    {
        return false;
    }

    for(int32 Idx = 0; Idx < Prims.Num(); ++Idx)
    {
        GA_Primitive* Prim = Prims[Idx];
        if(!Prim)
        {
            continue;
        }

        const GA_Offset PrimOffset = Prim->getMapOffset();
        UT_String AttributeValueRaw;
        AttributeValueRaw = AttributeHandle.get(PrimOffset);
        FString AttributeValue = UTF8_TO_TCHAR(AttributeValueRaw.c_str());

        Values.Add(AttributeValue);
    }

    return Values.Num() > 0;
}


bool
FHoudiniNodeAttributePrimitive::Get(const TArray<GA_Primitive*>& Prims, TArray<UObject*>& Values) const
{
    Values.Empty();

    if(!IsValid())
    {
        return false;
    }

    GA_RWHandleS AttributeHandle = FindAttributeHandle<GA_RWHandleS>(1);
    if(!AttributeHandle.isValid())
    {
        return false;
    }

    for(int32 Idx = 0; Idx < Prims.Num(); ++Idx)
    {
        GA_Primitive* Prim = Prims[Idx];
        if(!Prim)
        {
            continue;
        }

        const GA_Offset PrimOffset = Prim->getMapOffset();
        UT_String AttributeValueRaw;
        AttributeValueRaw = AttributeHandle.get(PrimOffset);
        FString AttributeValue = UTF8_TO_TCHAR(AttributeValueRaw.c_str());

        UObject* FoundObject = nullptr;

        if(!AttributeValue.IsEmpty())
        {
            FoundObject = StaticLoadObject(UObject::StaticClass(), nullptr, *AttributeValue, nullptr,
                LOAD_None, nullptr);
        }

        Values.Add(FoundObject);
    }

    return Values.Num() > 0;
}


bool
FHoudiniNodeAttributePrimitive::Get(const TArray<GA_Primitive*>& Prims, bool bScale, TArray<FVector>& Values) const
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

    const float Scale = Detail.GetScale();

    for(int32 Idx = 0; Idx < Prims.Num(); ++Idx)
    {
        GA_Primitive* Prim = Prims[Idx];
        if(!Prim)
        {
            continue;
        }

        const GA_Offset PrimOffset = Prim->getMapOffset();
        const UT_Vector3& AttributeValue = AttributeHandle.get(PrimOffset);

        FVector Value(AttributeValue.x(), AttributeValue.y(), AttributeValue.z());
        Swap(Value.Y, Value.Z);

        if(bScale)
        {
            Value *= Scale;
        }

        Values.Add(Value);
    }

    return Values.Num() > 0;
}


bool
FHoudiniNodeAttributePrimitive::Get(const TArray<GA_Primitive*>& Prims, TArray<FQuat>& Values) const
{
    Values.Empty();

    if(!IsValid())
    {
        return false;
    }

    GA_RWHandleV4 AttributeHandle = FindAttributeHandle<GA_RWHandleV4>(4);
    if(!AttributeHandle.isValid())
    {
        return false;
    }

    for(int32 Idx = 0; Idx < Prims.Num(); ++Idx)
    {
        GA_Primitive* Prim = Prims[Idx];
        if(!Prim)
        {
            continue;
        }

        const GA_Offset PrimOffset = Prim->getMapOffset();
        const UT_Quaternion& AttributeValue = AttributeHandle.get(PrimOffset);

        FQuat Value(AttributeValue.x(), AttributeValue.y(), AttributeValue.z(), AttributeValue.w());
        Swap(Value.Y, Value.Z);
        Value.W *= -1.0f;

        Values.Add(Value);
    }

    return Values.Num() > 0;
}


bool
FHoudiniNodeAttributePrimitive::Get(const TArray<GA_Primitive*>& Prims, bool bSwap, TArray<FVector2D>& Values) const
{
    Values.Empty();

    if(!IsValid())
    {
        return false;
    }

    GA_RWHandleV2 AttributeHandle = FindAttributeHandle<GA_RWHandleV2>(2);
    if(!AttributeHandle.isValid())
    {
        return false;
    }

    for(int32 Idx = 0; Idx < Prims.Num(); ++Idx)
    {
        GA_Primitive* Prim = Prims[Idx];
        if(!Prim)
        {
            continue;
        }

        const GA_Offset PrimOffset = Prim->getMapOffset();
        const UT_Vector2& AttributeValue = AttributeHandle.get(PrimOffset);

        FVector2D Value(AttributeValue.x(), AttributeValue.y());

        if(bSwap)
        {
            Value.Y = 1.0f - Value.Y;
        }

        Values.Add(Value);
    }

    return Values.Num() > 0;
}


bool
FHoudiniNodeAttributePrimitive::Get(const TArray<GA_Primitive*>& Prims, TArray<FColor>& Values) const
{
    Values.Empty();

    TArray<FLinearColor> LinearValues;
    if(Get(Prims, LinearValues))
    {
        for(int32 Idx = 0; Idx < LinearValues.Num(); ++Idx)
        {
            const FLinearColor& LinearColor = LinearValues[Idx];
            const FColor& Color = LinearColor.ToFColor(false);
            Values.Add(Color);
        }
    }

    return Values.Num() > 0;
}


bool
FHoudiniNodeAttributePrimitive::Get(const TArray<GA_Primitive*>& Prims, TArray<FLinearColor>& Values) const
{
    Values.Empty();

    if(!IsValid())
    {
        return false;
    }

    bool bSuccess = false;

    {
        GA_RWHandleV3 AttributeHandle = FindAttributeHandle<GA_RWHandleV3>(3);
        if(AttributeHandle.isValid())
        {
            for(int32 Idx = 0; Idx < Prims.Num(); ++Idx)
            {
                GA_Primitive* Prim = Prims[Idx];
                if(!Prim)
                {
                    continue;
                }

                const GA_Offset PrimOffset = Prim->getMapOffset();
                const UT_Vector3& AttributeValue = AttributeHandle.get(PrimOffset);

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
            for(int32 Idx = 0; Idx < Prims.Num(); ++Idx)
            {
                GA_Primitive* Prim = Prims[Idx];
                if(!Prim)
                {
                    continue;
                }

                const GA_Offset PrimOffset = Prim->getMapOffset();
                const UT_Vector4& AttributeValue = AttributeHandle.get(PrimOffset);

                FLinearColor Value(AttributeValue.x(), AttributeValue.y(), AttributeValue.z(), AttributeValue.w());
                Values.Add(Value);
            }
        }
    }

    return Values.Num() > 0;
}


bool
FHoudiniNodeAttributePrimitive::GetAll(TArray<int32>& Values) const
{
    Values.Empty();

    if(!IsValid())
    {
        return false;
    }

    GA_RWHandleI AttributeHandle = FindAttributeHandle<GA_RWHandleI>(1);
    if(!AttributeHandle.isValid())
    {
        return false;
    }

    GU_Detail* DetailPtr = Detail.GetDetail();
    GA_Primitive* Prim = nullptr;

    GA_FOR_ALL_PRIMITIVES(DetailPtr, Prim)
    {
        if(!Prim)
        {
            continue;
        }

        const GA_Offset PrimOffset = Prim->getMapOffset();
        const int32 AttributeValue = AttributeHandle.get(PrimOffset);

        Values.Add(AttributeValue);
    }

    return Values.Num() > 0;
}


bool
FHoudiniNodeAttributePrimitive::GetAll(TArray<FString>& Values) const
{
    Values.Empty();

    if(!IsValid())
    {
        return false;
    }

    GA_RWHandleS AttributeHandle = FindAttributeHandle<GA_RWHandleS>(1);
    if(!AttributeHandle.isValid())
    {
        return false;
    }

    GU_Detail* DetailPtr = Detail.GetDetail();
    GA_Primitive* Prim = nullptr;

    GA_FOR_ALL_PRIMITIVES(DetailPtr, Prim)
    {
        if(!Prim)
        {
            continue;
        }

        const GA_Offset PrimOffset = Prim->getMapOffset();
        UT_String AttributeValueRaw;
        AttributeValueRaw = AttributeHandle.get(PrimOffset);
        FString AttributeValue = UTF8_TO_TCHAR(AttributeValueRaw.c_str());

        Values.Add(AttributeValue);
    }

    return Values.Num() > 0;
}


bool
FHoudiniNodeAttributePrimitive::GetAll(TArray<UObject*>& Values) const
{
    Values.Empty();

    if(!IsValid())
    {
        return false;
    }

    GA_RWHandleS AttributeHandle = FindAttributeHandle<GA_RWHandleS>(1);
    if(!AttributeHandle.isValid())
    {
        return false;
    }

    GU_Detail* DetailPtr = Detail.GetDetail();
    GA_Primitive* Prim = nullptr;

    GA_FOR_ALL_PRIMITIVES(DetailPtr, Prim)
    {
        if(!Prim)
        {
            continue;
        }

        const GA_Offset PrimOffset = Prim->getMapOffset();
        UT_String AttributeValueRaw;
        AttributeValueRaw = AttributeHandle.get(PrimOffset);
        FString AttributeValue = UTF8_TO_TCHAR(AttributeValueRaw.c_str());

        UObject* FoundObject = nullptr;

        if(!AttributeValue.IsEmpty())
        {
            FoundObject = StaticLoadObject(UObject::StaticClass(), nullptr, *AttributeValue, nullptr,
                LOAD_None, nullptr);
        }

        Values.Add(FoundObject);
    }

    return Values.Num() > 0;
}


bool
FHoudiniNodeAttributePrimitive::GetAll(bool bScale, TArray<FVector>& Values) const
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

    const float Scale = Detail.GetScale();
    GU_Detail* DetailPtr = Detail.GetDetail();

    GA_Primitive* Prim = nullptr;

    GA_FOR_ALL_PRIMITIVES(DetailPtr, Prim)
    {
        if(!Prim)
        {
            continue;
        }

        const GA_Offset PrimOffset = Prim->getMapOffset();
        const UT_Vector3& AttributeValue = AttributeHandle.get(PrimOffset);

        FVector Value(AttributeValue.x(), AttributeValue.y(), AttributeValue.z());
        Swap(Value.Y, Value.Z);

        if(bScale)
        {

            Value *= Scale;
        }

        Values.Add(Value);
    }

    return Values.Num() > 0;
}


bool
FHoudiniNodeAttributePrimitive::GetAll(TArray<FQuat>& Values) const
{
    Values.Empty();

    if(!IsValid())
    {
        return false;
    }

    GA_RWHandleV4 AttributeHandle = FindAttributeHandle<GA_RWHandleV4>(4);
    if(!AttributeHandle.isValid())
    {
        return false;
    }

    GU_Detail* DetailPtr = Detail.GetDetail();
    GA_Primitive* Prim = nullptr;

    GA_FOR_ALL_PRIMITIVES(DetailPtr, Prim)
    {
        if(!Prim)
        {
            continue;
        }

        const GA_Offset PrimOffset = Prim->getMapOffset();
        const UT_Quaternion& AttributeValue = AttributeHandle.get(PrimOffset);

        FQuat Value(AttributeValue.x(), AttributeValue.y(), AttributeValue.z(), AttributeValue.w());
        Swap(Value.Y, Value.Z);
        Value.W *= -1.0f;

        Values.Add(Value);
    }

    return Values.Num() > 0;
}


bool
FHoudiniNodeAttributePrimitive::GetAll(TArray<FVector2D>& Values) const
{
    Values.Empty();

    if(!IsValid())
    {
        return false;
    }

    GA_RWHandleV2 AttributeHandle = FindAttributeHandle<GA_RWHandleV2>(2);
    if(!AttributeHandle.isValid())
    {
        return false;
    }

    GU_Detail* DetailPtr = Detail.GetDetail();
    GA_Primitive* Prim = nullptr;

    GA_FOR_ALL_PRIMITIVES(DetailPtr, Prim)
    {
        if(!Prim)
        {
            continue;
        }

        const GA_Offset PrimOffset = Prim->getMapOffset();
        const UT_Vector2& AttributeValue = AttributeHandle.get(PrimOffset);

        FVector2D Value(AttributeValue.x(), AttributeValue.y());
        Values.Add(Value);
    }

    return Values.Num() > 0;
}


bool
FHoudiniNodeAttributePrimitive::GetAll(TArray<FColor>& Values) const
{
    Values.Empty();

    TArray<FLinearColor> LinearValues;
    if(GetAll(LinearValues))
    {
        for(int32 Idx = 0; Idx < LinearValues.Num(); ++Idx)
        {
            const FLinearColor& LinearColor = LinearValues[Idx];
            const FColor& Color = LinearColor.ToFColor(false);
            Values.Add(Color);
        }
    }

    return Values.Num() > 0;
}


bool
FHoudiniNodeAttributePrimitive::GetAll(TArray<FLinearColor>& Values) const
{
    Values.Empty();

    if(!IsValid())
    {
        return false;
    }

    GU_Detail* DetailPtr = Detail.GetDetail();
    bool bSuccess = false;

    {
        GA_RWHandleV3 AttributeHandle = FindAttributeHandle<GA_RWHandleV3>(3);
        if(AttributeHandle.isValid())
        {
            GA_Primitive* Prim = nullptr;
            GA_FOR_ALL_PRIMITIVES(DetailPtr, Prim)
            {
                if(!Prim)
                {
                    continue;
                }

                const GA_Offset PrimOffset = Prim->getMapOffset();
                const UT_Vector3& AttributeValue = AttributeHandle.get(PrimOffset);

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
            GA_Primitive* Prim = nullptr;
            GA_FOR_ALL_PRIMITIVES(DetailPtr, Prim)
            {
                if(!Prim)
                {
                    continue;
                }

                const GA_Offset PrimOffset = Prim->getMapOffset();
                const UT_Vector4& AttributeValue = AttributeHandle.get(PrimOffset);

                FLinearColor Value(AttributeValue.x(), AttributeValue.y(), AttributeValue.z(), AttributeValue.w());
                Values.Add(Value);
            }
        }
    }

    return Values.Num() > 0;
}



#pragma warning(pop)

