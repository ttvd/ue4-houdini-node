#pragma once
#include "HoudiniNodeVariantType.h"


class HOUDININODE_API FHoudiniNodeVariant
{

    friend FArchive& operator<<(FArchive& Ar, FHoudiniNodeVariant& Variant);

public:

    FHoudiniNodeVariant();
    FHoudiniNodeVariant(const FHoudiniNodeVariant& Variant);

public:

    bool operator==(const FHoudiniNodeVariant& Variant) const;

public:

    FHoudiniNodeVariant(bool bValue);

    FHoudiniNodeVariant(int8 Value);
    FHoudiniNodeVariant(int16 Value);
    FHoudiniNodeVariant(int32 Value);
    FHoudiniNodeVariant(int64 Value);

    FHoudiniNodeVariant(float Value);
    FHoudiniNodeVariant(double Value);

    FHoudiniNodeVariant(uint8 Value);
    FHoudiniNodeVariant(uint16 Value);
    FHoudiniNodeVariant(uint32 Value);
    FHoudiniNodeVariant(uint64 Value);

    FHoudiniNodeVariant(const FString& Value);
    FHoudiniNodeVariant(const FName& Value);

    FHoudiniNodeVariant(const FVector& Value, bool bScale);
    FHoudiniNodeVariant(const FVector2D& Value, bool bUVSwap);
    FHoudiniNodeVariant(const FVector4& Value, bool bScale);
    FHoudiniNodeVariant(const FQuat& Value);
    FHoudiniNodeVariant(const FRotator& Value);
    FHoudiniNodeVariant(const FTransform& Value, bool bScale);

    FHoudiniNodeVariant(const FColor& Value);
    FHoudiniNodeVariant(const FLinearColor& Value);

    FHoudiniNodeVariant(const FBox& Value, bool bScale);
    FHoudiniNodeVariant(const FBoxSphereBounds& Value, bool bScale);

    FHoudiniNodeVariant(const TArray<FHoudiniNodeVariant>& Value);
    FHoudiniNodeVariant(const TMap<FString, FHoudiniNodeVariant>& Value);

public:

    //! Return the type of this variant.
    EHoudiniNodeVariantType::Enum GetType() const;

    //! Return true if this variant is null.
    bool IsNull() const;

    //! Return true if this is a container type.
    bool IsContainer() const;

protected:

    //! Type of this variant.
    EHoudiniNodeVariantType::Enum VariantType;

    //! Variant value.
    TArray<uint8> VariantValue;
};
