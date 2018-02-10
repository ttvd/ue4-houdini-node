#pragma once

#include "Archive.h"


class UObject;


class HOUDININODE_API FHoudiniNodeArchive
{
public:

    FHoudiniNodeArchive();
    virtual ~FHoudiniNodeArchive();

public:

    /*
    //! Serialize bytes.
    virtual FHoudiniNodeArchive& operator<<(const FString& Key, void* Data, int64 Length);

    //! Type serialization functions.
    virtual FHoudiniNodeArchive& operator<<(const FString& Key, const FName& Name);

    virtual FHoudiniNodeArchive& operator<<(const FString& Key, const FString& String);
    virtual FHoudiniNodeArchive& operator<<(const FString& Key, const TArray<FString>& Strings);

    //! Serialization of primitive types.
    virtual FHoudiniNodeArchive& operator<<(const FString& Key, bool bValue);

    virtual FHoudiniNodeArchive& operator<<(const FString& Key, float Value);
    virtual FHoudiniNodeArchive& operator<<(const FString& Key, const TArray<float>& Values);

    virtual FHoudiniNodeArchive& operator<<(const FString& Key, int8 Value);
    virtual FHoudiniNodeArchive& operator<<(const FString& Key, const TArray<int8>& Values);

    virtual FHoudiniNodeArchive& operator<<(const FString& Key, int16 Value);
    virtual FHoudiniNodeArchive& operator<<(const FString& Key, const TArray<int16>& Values);

    virtual FHoudiniNodeArchive& operator<<(const FString& Key, int32 Value);
    virtual FHoudiniNodeArchive& operator<<(const FString& Key, const TArray<int32>& Values);

    virtual FHoudiniNodeArchive& operator<<(const FString& Key, int64 Value);
    virtual FHoudiniNodeArchive& operator<<(const FString& Key, const TArray<int64>& Values);

    virtual FHoudiniNodeArchive& operator<<(const FString& Key, uint8 Value);
    virtual FHoudiniNodeArchive& operator<<(const FString& Key, const TArray<uint8>& Values);

    virtual FHoudiniNodeArchive& operator<<(const FString& Key, uint16 Value);
    virtual FHoudiniNodeArchive& operator<<(const FString& Key, const TArray<uint16>& Values);

    virtual FHoudiniNodeArchive& operator<<(const FString& Key, uint32 Value);
    virtual FHoudiniNodeArchive& operator<<(const FString& Key, const TArray<uint32>& Values);

    virtual FHoudiniNodeArchive& operator<<(const FString& Key, uint64 Value);
    virtual FHoudiniNodeArchive& operator<<(const FString& Key, const TArray<uint64>& Values);

    //! Serialization of math types.
    virtual FHoudiniNodeArchive& operator<<(const FString& Key, const FVector& Data, bool bScale);
    virtual FHoudiniNodeArchive& operator<<(const FString& Key, const TArray<FVector>& Data, bool bScale);

    virtual FHoudiniNodeArchive& operator<<(const FString& Key, const FVector2D& Data, bool bUVSwap);
    virtual FHoudiniNodeArchive& operator<<(const FString& Key, const TArray<FVector2D>& Data, bool bUVSwap);

    virtual FHoudiniNodeArchive& operator<<(const FString& Key, const FQuat& Data);
    virtual FHoudiniNodeArchive& operator<<(const FString& Key, const TArray<FQuat>& Data);

    virtual FHoudiniNodeArchive& operator<<(const FString& Key, const FRotator& Data);
    virtual FHoudiniNodeArchive& operator<<(const FString& Key, const TArray<FRotator>& Data);

    virtual FHoudiniNodeArchive& operator<<(const FString& Key, const FTransform& Data, bool bSwap);
    virtual FHoudiniNodeArchive& operator<<(const FString& Key, const TArray<FTransform>& Data, bool bSwap);

    //! Serialization of objects.
    virtual FHoudiniNodeArchive& operator<<(const FString& Key, UObject* Object);
    virtual FHoudiniNodeArchive& operator<<(const FString& Key, const TArray<UObject*>& Objects);

    //! Serialize another archive.
    virtual FHoudiniNodeArchive& operator<<(const FString& Key, const FHoudiniNodeArchive& Archive);
    */
};
