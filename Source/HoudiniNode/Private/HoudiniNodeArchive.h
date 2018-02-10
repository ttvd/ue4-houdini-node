#pragma once
#include "HoudiniNodeVariant.h"


class UObject;


class HOUDININODE_API FHoudiniNodeArchive
{
public:

    FHoudiniNodeArchive();
    virtual ~FHoudiniNodeArchive();

public:

    //! Pack this archive into a given byte array.
    bool Pack(TArray<char>& PackedBuffer) const;

public:

    //! Encode values.
    template <typename TType> FHoudiniNodeArchive& Encode(const TType& Value);
    template <typename TType> FHoudiniNodeArchive& Encode(const TArray<TType>& Values);

    //! Encode values with a boolean option.
    template <typename TType> FHoudiniNodeArchive& EncodeOption(const TType& Value, bool bOption);
    template <typename TType> FHoudiniNodeArchive& EncodeOption(const TArray<TType>& Values, bool bOption);

protected:

    //! Storage for this archive.
    TArray<FHoudiniNodeVariant> Buffer;
};


template <typename TType>
FHoudiniNodeArchive&
FHoudiniNodeArchive::Encode(const TType& Value)
{
    Buffer.Add(Value);
    return *this;
}


template <typename TType>
FHoudiniNodeArchive&
FHoudiniNodeArchive::Encode(const TArray<TType>& Values)
{
    TArray<FHoudiniNodeVariant> Array;

    for(int32 Idx = 0; Idx < Values.Num(); ++Idx)
    {
        const TType& Value = Values[Idx];
        FHoudiniNodeVariant Variant(Value);
        Array.Add(Variant);
    }

    if(Array.Num() > 0)
    {
        Buffer.Add(Array);
    }

    return *this;
}


template <typename TType>
FHoudiniNodeArchive&
FHoudiniNodeArchive::EncodeOption(const TType& Value, bool bOption)
{
    FHoudiniNodeVariant Variant(Value, bOption);
    Buffer.Add(Variant);

    return *this;
}


template <typename TType>
FHoudiniNodeArchive&
FHoudiniNodeArchive::EncodeOption(const TArray<TType>& Values, bool bOption)
{
    TArray<FHoudiniNodeVariant> Variants;

    for(int32 Idx = 0; Idx < Values.Num(); ++Idx)
    {
        const TType& Value = Values[Idx];
        FHoudiniNodeVariant Variant(Value, bOption);

        Variants.Add(Variant);
    }

    if(Variants.Num() > 0)
    {
        Buffer.Add(Variants);
    }

    return *this;
}
