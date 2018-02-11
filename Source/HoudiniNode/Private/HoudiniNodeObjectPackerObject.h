#pragma once
#include "HoudiniNodeObjectPackerObject.generated.h"

class UProperty;
class UByteProperty;
class UStructProperty;
class UInt8Property;
class UInt16Property;
class UIntProperty;
class UInt64Property;
class UUInt16Property;
class UUInt32Property;
class UUInt64Property;
class UFloatProperty;
class UDoubleProperty;
class UBoolProperty;
class UObjectProperty;
class UClassProperty;
class UNameProperty;
class UStrProperty;
class UArrayProperty;
class UMapProperty;
class USetProperty;


UCLASS()
class HOUDININODE_API UHoudiniNodeObjectPackerObject : public UHoudiniNodeObjectPacker
{
    GENERATED_UCLASS_BODY()

public:

    //! Pack the object of this type.
    virtual bool Encode(UObject* Object, TMap<FString, FHoudiniNodeVariant>& ObjectMap) const;

private:

    //! Property conversion functions.
    bool EncodeProperty(UProperty* Property, UObject* Object, TMap<FString, FHoudiniNodeVariant>& ObjectMap) const;

    bool EncodeProperty(UByteProperty* Property, UObject* Object, TMap<FString, FHoudiniNodeVariant>& ObjectMap) const;
    bool EncodeProperty(UInt8Property* Property, UObject* Object, TMap<FString, FHoudiniNodeVariant>& ObjectMap) const;
    bool EncodeProperty(UInt16Property* Property, UObject* Object, TMap<FString, FHoudiniNodeVariant>& ObjectMap) const;
    bool EncodeProperty(UIntProperty* Property, UObject* Object, TMap<FString, FHoudiniNodeVariant>& ObjectMap) const;
    bool EncodeProperty(UInt64Property* Property, UObject* Object, TMap<FString, FHoudiniNodeVariant>& ObjectMap) const;
    bool EncodeProperty(UUInt16Property* Property, UObject* Object, TMap<FString, FHoudiniNodeVariant>& ObjectMap) const;
    bool EncodeProperty(UUInt32Property* Property, UObject* Object, TMap<FString, FHoudiniNodeVariant>& ObjectMap) const;
    bool EncodeProperty(UUInt64Property* Property, UObject* Object, TMap<FString, FHoudiniNodeVariant>& ObjectMap) const;
    bool EncodeProperty(UFloatProperty* Property, UObject* Object, TMap<FString, FHoudiniNodeVariant>& ObjectMap) const;
    bool EncodeProperty(UDoubleProperty* Property, UObject* Object, TMap<FString, FHoudiniNodeVariant>& ObjectMap) const;
    bool EncodeProperty(UBoolProperty* Property, UObject* Object, TMap<FString, FHoudiniNodeVariant>& ObjectMap) const;

    bool EncodeProperty(UObjectProperty* Property, UObject* Object, TMap<FString, FHoudiniNodeVariant>& ObjectMap) const;
    bool EncodeProperty(UClassProperty* Property, UObject* Object, TMap<FString, FHoudiniNodeVariant>& ObjectMap) const;

    bool EncodeProperty(UNameProperty* Property, UObject* Object, TMap<FString, FHoudiniNodeVariant>& ObjectMap) const;
    bool EncodeProperty(UStrProperty* Property, UObject* Object, TMap<FString, FHoudiniNodeVariant>& ObjectMap) const;

    bool EncodeProperty(UArrayProperty* Property, UObject* Object, TMap<FString, FHoudiniNodeVariant>& ObjectMap) const;
    bool EncodeProperty(UMapProperty* Property, UObject* Object, TMap<FString, FHoudiniNodeVariant>& ObjectMap) const;
    bool EncodeProperty(USetProperty* Property, UObject* Object, TMap<FString, FHoudiniNodeVariant>& ObjectMap) const;

    bool EncodeProperty(UStructProperty* Property, UObject* Object, TMap<FString, FHoudiniNodeVariant>& ObjectMap) const;

private:

    //! Helper function which encodes primitive types.
    template <typename TType> bool EncodePropertyPrimitive(UProperty* Property, UObject* Object,
        TMap<FString, FHoudiniNodeVariant>& ObjectMap) const;
};


template <typename TType>
bool
UHoudiniNodeObjectPackerObject::EncodePropertyPrimitive(UProperty* Property, UObject* Object,
    TMap<FString, FHoudiniNodeVariant>& ObjectMap) const
{
    const int32 Offset = Property->GetOffset_ForDebug();
    TType Value = *((TType*)((const char*) Object) + Offset);

    const FString& PropertyName = Property->GetName();
    ObjectMap.Add(PropertyName, Value);

    return true;
}
