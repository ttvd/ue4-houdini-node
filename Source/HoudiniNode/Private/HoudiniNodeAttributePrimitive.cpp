#include "HoudiniNodePrivatePCH.h"
#include "HoudiniNodeAttributePrimitive.h"

#pragma warning(push)
#pragma warning(disable : 4706)


FHoudiniNodeAttributePrimitive::FHoudiniNodeAttributePrimitive(GU_Detail* InDetail, const FString& InName) :
    FHoudiniNodeAttribute(InDetail, InName, GA_ATTRIB_PRIMITIVE)
{

}


bool
FHoudiniNodeAttributePrimitive::SelectNonZero(TArray<GA_Primitive*>& Prims) const
{
    GA_RWHandleI AttributeHandle = FindAttributeHandle<GA_RWHandleI>(1);
    if(!AttributeHandle.isValid())
    {
        return false;
    }

    GA_Primitive* Prim = nullptr;

    GA_FOR_ALL_PRIMITIVES(Detail, Prim)
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
    GA_RWHandleI AttributeHandle = FindAttributeHandle<GA_RWHandleI>(1);
    if(!AttributeHandle.isValid())
    {
        return false;
    }

    GA_Primitive* Prim = nullptr;

    GA_FOR_ALL_PRIMITIVES(Detail, Prim)
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

    GA_RWHandleS AttributeHandle = FindAttributeHandle<GA_RWHandleS>(1);
    if(!AttributeHandle.isValid())
    {
        return false;
    }

    std::string RawString = TCHAR_TO_UTF8(*Value);
    UT_String RawValue(RawString);

    GA_Primitive* Prim = nullptr;

    GA_FOR_ALL_PRIMITIVES(Detail, Prim)
    {
        if(!Prim)
        {
            continue;
        }

        const GA_Offset PrimOffset = Prim->getMapOffset();
        const UT_String& AttributeValue = AttributeHandle.get(PrimOffset);

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

    FString ObjectPath(TEXT(""));

    if(Object)
    {
        ObjectPath = Object->GetPathName();
    }

    return Select(ObjectPath, Prims);
}


bool
FHoudiniNodeAttributePrimitive::Group(TMap<int32, TArray<GA_Primitive*> >& Prims) const
{
    Prims.Empty();

    GA_RWHandleI AttributeHandle = FindAttributeHandle<GA_RWHandleI>(1);
    if(!AttributeHandle.isValid())
    {
        return false;
    }

    GA_Primitive* Prim = nullptr;

    GA_FOR_ALL_PRIMITIVES(Detail, Prim)
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

    GA_RWHandleS AttributeHandle = FindAttributeHandle<GA_RWHandleS>(1);
    if(!AttributeHandle.isValid())
    {
        return false;
    }

    GA_Primitive* Prim = nullptr;

    GA_FOR_ALL_PRIMITIVES(Detail, Prim)
    {
        if(!Prim)
        {
            continue;
        }

        const GA_Offset PrimOffset = Prim->getMapOffset();
        const UT_String& AttributeValueRaw = AttributeHandle.get(PrimOffset);
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

    GA_RWHandleS AttributeHandle = FindAttributeHandle<GA_RWHandleS>(1);
    if(!AttributeHandle.isValid())
    {
        return false;
    }

    GA_Primitive* Prim = nullptr;

    GA_FOR_ALL_PRIMITIVES(Detail, Prim)
    {
        if(!Prim)
        {
            continue;
        }

        const GA_Offset PrimOffset = Prim->getMapOffset();
        const UT_String& AttributeValueRaw = AttributeHandle.get(PrimOffset);

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
        const UT_String& AttributeValueRaw = AttributeHandle.get(PrimOffset);
        FString AttributeValue = UTF8_TO_TCHAR(AttributeValueRaw.c_str());

        Values.Add(AttributeValue);
    }

    return Values.Num() > 0;
}


bool
FHoudiniNodeAttributePrimitive::Get(const TArray<GA_Primitive*>& Prims, TArray<UObject*>& Values) const
{
    Values.Empty();

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
        const UT_String& AttributeValueRaw = AttributeHandle.get(PrimOffset);
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
FHoudiniNodeAttributePrimitive::GetAll(TArray<int32>& Values) const
{
    Values.Empty();

    GA_RWHandleI AttributeHandle = FindAttributeHandle<GA_RWHandleI>(1);
    if(!AttributeHandle.isValid())
    {
        return false;
    }

    GA_Primitive* Prim = nullptr;

    GA_FOR_ALL_PRIMITIVES(Detail, Prim)
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

    GA_RWHandleS AttributeHandle = FindAttributeHandle<GA_RWHandleS>(1);
    if(!AttributeHandle.isValid())
    {
        return false;
    }

    GA_Primitive* Prim = nullptr;

    GA_FOR_ALL_PRIMITIVES(Detail, Prim)
    {
        if(!Prim)
        {
            continue;
        }

        const GA_Offset PrimOffset = Prim->getMapOffset();
        const UT_String& AttributeValueRaw = AttributeHandle.get(PrimOffset);
        FString AttributeValue = UTF8_TO_TCHAR(AttributeValueRaw.c_str());

        Values.Add(AttributeValue);
    }

    return Values.Num() > 0;
}


bool
FHoudiniNodeAttributePrimitive::GetAll(TArray<UObject*>& Values) const
{
    Values.Empty();

    GA_RWHandleS AttributeHandle = FindAttributeHandle<GA_RWHandleS>(1);
    if(!AttributeHandle.isValid())
    {
        return false;
    }

    GA_Primitive* Prim = nullptr;

    GA_FOR_ALL_PRIMITIVES(Detail, Prim)
    {
        if(!Prim)
        {
            continue;
        }

        const GA_Offset PrimOffset = Prim->getMapOffset();
        const UT_String& AttributeValueRaw = AttributeHandle.get(PrimOffset);
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

#pragma warning(pop)

