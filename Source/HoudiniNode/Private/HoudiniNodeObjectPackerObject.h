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
    virtual bool Encode(TMap<FString, FHoudiniNodeVariant>& ObjectMap, UObject* Object) const;

private:

    //! Property conversion functions.
    bool EncodeProperty(UProperty* Property) const;

    bool EncodeProperty(UByteProperty* Property) const;
    bool EncodeProperty(UInt8Property* Property) const;
    bool EncodeProperty(UInt16Property* Property) const;
    bool EncodeProperty(UIntProperty* Property) const;
    bool EncodeProperty(UInt64Property* Property) const;
    bool EncodeProperty(UUInt16Property* Property) const;
    bool EncodeProperty(UUInt32Property* Property) const;
    bool EncodeProperty(UUInt64Property* Property) const;
    bool EncodeProperty(UFloatProperty* Property) const;
    bool EncodeProperty(UDoubleProperty* Property) const;
    bool EncodeProperty(UBoolProperty* Property) const;

    bool EncodeProperty(UObjectProperty* Property) const;
    bool EncodeProperty(UClassProperty* Property) const;

    bool EncodeProperty(UNameProperty* Property) const;
    bool EncodeProperty(UStrProperty* Property) const;

    bool EncodeProperty(UArrayProperty* Property) const;
    bool EncodeProperty(UMapProperty* Property) const;
    bool EncodeProperty(USetProperty* Property) const;

    bool EncodeProperty(UStructProperty* Property) const;
};
