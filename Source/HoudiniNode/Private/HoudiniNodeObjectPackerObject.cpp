#include "HoudiniNodeObjectPackerObject.h"
#include "HoudiniNodePrivatePCH.h"


UHoudiniNodeObjectPackerObject::UHoudiniNodeObjectPackerObject(const FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer)
{
    SupportedClass = UObject::StaticClass();
}


bool
UHoudiniNodeObjectPackerObject::Encode(TMap<FString, FHoudiniNodeVariant>& ObjectMap, UObject* Object) const
{
    if(!Object)
    {
        return false;
    }

    UClass* ObjectClass = Object->GetClass();

    UProperty* Property = dynamic_cast<UProperty*>(ObjectClass->Children);
    while(Property)
    {
        EncodeProperty(Property);
        Property = dynamic_cast<UProperty*>(Property->Next);
    }

    return true;
}


bool
UHoudiniNodeObjectPackerObject::EncodeProperty(UProperty* Property) const
{
    return false;
}


bool
UHoudiniNodeObjectPackerObject::EncodeProperty(UByteProperty* Property) const
{
    return false;
}


bool
UHoudiniNodeObjectPackerObject::EncodeProperty(UInt8Property* Property) const
{
    return false;
}


bool
UHoudiniNodeObjectPackerObject::EncodeProperty(UInt16Property* Property) const
{
    return false;
}


bool
UHoudiniNodeObjectPackerObject::EncodeProperty(UIntProperty* Property) const
{
    return false;
}


bool
UHoudiniNodeObjectPackerObject::EncodeProperty(UInt64Property* Property) const
{
    return false;
}


bool
UHoudiniNodeObjectPackerObject::EncodeProperty(UUInt16Property* Property) const
{
    return false;
}


bool
UHoudiniNodeObjectPackerObject::EncodeProperty(UUInt32Property* Property) const
{
    return false;
}


bool
UHoudiniNodeObjectPackerObject::EncodeProperty(UUInt64Property* Property) const
{
    return false;
}


bool
UHoudiniNodeObjectPackerObject::EncodeProperty(UFloatProperty* Property) const
{
    return false;
}


bool
UHoudiniNodeObjectPackerObject::EncodeProperty(UDoubleProperty* Property) const
{
    return false;
}


bool
UHoudiniNodeObjectPackerObject::EncodeProperty(UBoolProperty* Property) const
{
    return false;
}


bool
UHoudiniNodeObjectPackerObject::EncodeProperty(UObjectProperty* Property) const
{
    return false;
}


bool
UHoudiniNodeObjectPackerObject::EncodeProperty(UClassProperty* Property) const
{
    return false;
}


bool
UHoudiniNodeObjectPackerObject::EncodeProperty(UNameProperty* Property) const
{
    return false;
}


bool
UHoudiniNodeObjectPackerObject::EncodeProperty(UStrProperty* Property) const
{
    return false;
}


bool
UHoudiniNodeObjectPackerObject::EncodeProperty(UArrayProperty* Property) const
{
    return false;
}


bool
UHoudiniNodeObjectPackerObject::EncodeProperty(UMapProperty* Property) const
{
    return false;
}


bool
UHoudiniNodeObjectPackerObject::EncodeProperty(USetProperty* Property) const
{
    return false;
}


bool
UHoudiniNodeObjectPackerObject::EncodeProperty(UStructProperty* Property) const
{
    return false;
}
