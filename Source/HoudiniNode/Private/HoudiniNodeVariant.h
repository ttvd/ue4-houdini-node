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

    //! Pack variant into a given stream (message pack protocol).
    void Pack(TArray<uint8>& PackedBuffer) const;

public:

    //! Return the type of this variant.
    EHoudiniNodeVariantType::Enum GetType() const;

    //! Return true if this variant is null.
    bool IsNull() const;

    //! Return true if this is a container type.
    bool IsContainer() const;

protected:

    //! Helper function used to pack data into a memory writer.
    void Pack(FMemoryWriter& Writer) const;

    //! Helper function used to pack integer types.
    void Pack(int64 Value, FMemoryWriter& Writer) const;
    void Pack(uint64 Value, FMemoryWriter& Writer) const;

    //! Helper function used to pack string types.
    void Pack(const FString& String, FMemoryWriter& Writer) const;

protected:

    //! Type of this variant.
    EHoudiniNodeVariantType::Enum VariantType;

    //! Variant value.
    TArray<uint8> VariantValue;
};


