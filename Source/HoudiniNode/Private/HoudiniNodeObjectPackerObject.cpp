#include "HoudiniNodeObjectPackerObject.h"
#include "HoudiniNodePrivatePCH.h"


UHoudiniNodeObjectPackerObject::UHoudiniNodeObjectPackerObject(const FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer)
{
    SupportedClass = UObject::StaticClass();
}


bool
UHoudiniNodeObjectPackerObject::Encode(UObject* Object, TMap<FString, FHoudiniNodeVariant>& ObjectMap) const
{
    if(!Object)
    {
        return false;
    }

    UClass* ObjectClass = Object->GetClass();

    UProperty* Property = dynamic_cast<UProperty*>(ObjectClass->Children);
    while(Property)
    {
        EncodeProperty(Property, Object, ObjectMap);
        Property = dynamic_cast<UProperty*>(Property->Next);
    }

    return true;
}


bool
UHoudiniNodeObjectPackerObject::EncodeProperty(UProperty* Property, UObject* Object,
    TMap<FString, FHoudiniNodeVariant>& ObjectMap) const
{
    return false;
}


bool
UHoudiniNodeObjectPackerObject::EncodeProperty(UByteProperty* Property, UObject* Object,
    TMap<FString, FHoudiniNodeVariant>& ObjectMap) const
{
    return EncodePropertyPrimitive<uint8>(Property, Object, ObjectMap);
}


bool
UHoudiniNodeObjectPackerObject::EncodeProperty(UInt8Property* Property, UObject* Object,
    TMap<FString, FHoudiniNodeVariant>& ObjectMap) const
{
    return EncodePropertyPrimitive<int8>(Property, Object, ObjectMap);
}


bool
UHoudiniNodeObjectPackerObject::EncodeProperty(UInt16Property* Property, UObject* Object,
    TMap<FString, FHoudiniNodeVariant>& ObjectMap) const
{
    return EncodePropertyPrimitive<int16>(Property, Object, ObjectMap);
}


bool
UHoudiniNodeObjectPackerObject::EncodeProperty(UIntProperty* Property, UObject* Object,
    TMap<FString, FHoudiniNodeVariant>& ObjectMap) const
{
    return EncodePropertyPrimitive<int32>(Property, Object, ObjectMap);
}


bool
UHoudiniNodeObjectPackerObject::EncodeProperty(UInt64Property* Property, UObject* Object,
    TMap<FString, FHoudiniNodeVariant>& ObjectMap) const
{
    return EncodePropertyPrimitive<int64>(Property, Object, ObjectMap);
}


bool
UHoudiniNodeObjectPackerObject::EncodeProperty(UUInt16Property* Property, UObject* Object,
    TMap<FString, FHoudiniNodeVariant>& ObjectMap) const
{
    return EncodePropertyPrimitive<uint16>(Property, Object, ObjectMap);
}


bool
UHoudiniNodeObjectPackerObject::EncodeProperty(UUInt32Property* Property, UObject* Object,
    TMap<FString, FHoudiniNodeVariant>& ObjectMap) const
{
    return EncodePropertyPrimitive<uint32>(Property, Object, ObjectMap);
}


bool
UHoudiniNodeObjectPackerObject::EncodeProperty(UUInt64Property* Property, UObject* Object,
    TMap<FString, FHoudiniNodeVariant>& ObjectMap) const
{
    return EncodePropertyPrimitive<uint64>(Property, Object, ObjectMap);
}


bool
UHoudiniNodeObjectPackerObject::EncodeProperty(UFloatProperty* Property, UObject* Object,
    TMap<FString, FHoudiniNodeVariant>& ObjectMap) const
{
    return EncodePropertyPrimitive<float>(Property, Object, ObjectMap);
}


bool
UHoudiniNodeObjectPackerObject::EncodeProperty(UDoubleProperty* Property, UObject* Object,
    TMap<FString, FHoudiniNodeVariant>& ObjectMap) const
{
    return EncodePropertyPrimitive<double>(Property, Object, ObjectMap);
}


bool
UHoudiniNodeObjectPackerObject::EncodeProperty(UBoolProperty* Property, UObject* Object,
    TMap<FString, FHoudiniNodeVariant>& ObjectMap) const
{
    void* ValueAddr = Property->ContainerPtrToValuePtr<void>(Object);
    bool bBoolValue = Property->GetPropertyValue(ValueAddr);

    const FString& PropertyName = Property->GetName();
    ObjectMap.Add(PropertyName, bBoolValue);

    return true;
}


bool
UHoudiniNodeObjectPackerObject::EncodeProperty(UObjectProperty* Property, UObject* Object,
    TMap<FString, FHoudiniNodeVariant>& ObjectMap) const
{
    return false;
}


bool
UHoudiniNodeObjectPackerObject::EncodeProperty(UClassProperty* Property, UObject* Object,
    TMap<FString, FHoudiniNodeVariant>& ObjectMap) const
{
    return false;
}


bool
UHoudiniNodeObjectPackerObject::EncodeProperty(UNameProperty* Property, UObject* Object,
    TMap<FString, FHoudiniNodeVariant>& ObjectMap) const
{
    void* ValueAddr = Property->ContainerPtrToValuePtr<void>(Object);
    const FName& Name = Property->GetPropertyValue(ValueAddr);
    const FString& String = Name.ToString();

    const FString& PropertyName = Property->GetName();
    ObjectMap.Add(PropertyName, String);

    return true;
}


bool
UHoudiniNodeObjectPackerObject::EncodeProperty(UStrProperty* Property, UObject* Object,
    TMap<FString, FHoudiniNodeVariant>& ObjectMap) const
{
    void* ValueAddr = Property->ContainerPtrToValuePtr<void>(Object);
    const FString& String = Property->GetPropertyValue(ValueAddr);

    const FString& PropertyName = Property->GetName();
    ObjectMap.Add(PropertyName, String);

    return true;
}


bool
UHoudiniNodeObjectPackerObject::EncodeProperty(UArrayProperty* Property, UObject* Object,
    TMap<FString, FHoudiniNodeVariant>& ObjectMap) const
{
    return false;
}


bool
UHoudiniNodeObjectPackerObject::EncodeProperty(UMapProperty* Property, UObject* Object,
    TMap<FString, FHoudiniNodeVariant>& ObjectMap) const
{
    return false;
}


bool
UHoudiniNodeObjectPackerObject::EncodeProperty(USetProperty* Property, UObject* Object,
    TMap<FString, FHoudiniNodeVariant>& ObjectMap) const
{
    return false;
}


bool
UHoudiniNodeObjectPackerObject::EncodeProperty(UStructProperty* Property, UObject* Object,
    TMap<FString, FHoudiniNodeVariant>& ObjectMap) const
{
    return false;
}
