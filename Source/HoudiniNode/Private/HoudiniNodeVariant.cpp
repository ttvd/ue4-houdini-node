#include "HoudiniNodeVariant.h"
#include "HoudiniNodePrivatePCH.h"


FArchive&
operator<<(FArchive& Ar, FHoudiniNodeVariant& Variant)
{
    int32 TypeValue = (int32) Variant.VariantType;
    Ar << TypeValue;

    if(Ar.IsLoading())
    {
        Variant.VariantType = (EHoudiniNodeVariantType::Enum) TypeValue;
    }

    Ar << Variant.VariantValue;

    return Ar;
}


FHoudiniNodeVariant::FHoudiniNodeVariant() :
    VariantType(EHoudiniNodeVariantType::Null)
{

}


FHoudiniNodeVariant::FHoudiniNodeVariant(const FHoudiniNodeVariant& Variant) :
    VariantType(Variant.VariantType),
    VariantValue(Variant.VariantValue)
{

}


bool
FHoudiniNodeVariant::operator==(const FHoudiniNodeVariant& Variant) const
{
    if(VariantType == Variant.VariantType)
    {
        const int32 VariantBytes = VariantValue.Num();
        if(VariantBytes == Variant.VariantValue.Num())
        {
            if(!VariantBytes)
            {
                return true;
            }

            return !FMemory::Memcmp(&VariantValue[0], &Variant.VariantValue[0], VariantBytes);
        }
    }

    return false;
}


FHoudiniNodeVariant::FHoudiniNodeVariant(bool bValue) :
    VariantType(EHoudiniNodeVariantType::Bool)
{
    FMemoryWriter Writer(VariantValue, true);
    Writer << bValue;
}


FHoudiniNodeVariant::FHoudiniNodeVariant(int8 Value) :
    VariantType(EHoudiniNodeVariantType::Int8)
{
    FMemoryWriter Writer(VariantValue, true);
    Writer << Value;
}


FHoudiniNodeVariant::FHoudiniNodeVariant(int16 Value) :
    VariantType(EHoudiniNodeVariantType::Int16)
{
    FMemoryWriter Writer(VariantValue, true);
    Writer << Value;
}


FHoudiniNodeVariant::FHoudiniNodeVariant(int32 Value) :
    VariantType(EHoudiniNodeVariantType::Int32)
{
    FMemoryWriter Writer(VariantValue, true);
    Writer << Value;
}


FHoudiniNodeVariant::FHoudiniNodeVariant(int64 Value) :
    VariantType(EHoudiniNodeVariantType::Int64)
{
    FMemoryWriter Writer(VariantValue, true);
    Writer << Value;
}


FHoudiniNodeVariant::FHoudiniNodeVariant(float Value) :
    VariantType(EHoudiniNodeVariantType::Float)
{
    FMemoryWriter Writer(VariantValue, true);
    Writer << Value;
}


FHoudiniNodeVariant::FHoudiniNodeVariant(double Value) :
    VariantType(EHoudiniNodeVariantType::Double)
{
    FMemoryWriter Writer(VariantValue, true);
    Writer << Value;
}


FHoudiniNodeVariant::FHoudiniNodeVariant(uint8 Value) :
    VariantType(EHoudiniNodeVariantType::UInt8)
{
    FMemoryWriter Writer(VariantValue, true);
    Writer << Value;
}


FHoudiniNodeVariant::FHoudiniNodeVariant(uint16 Value) :
    VariantType(EHoudiniNodeVariantType::UInt16)
{
    FMemoryWriter Writer(VariantValue, true);
    Writer << Value;
}


FHoudiniNodeVariant::FHoudiniNodeVariant(uint32 Value) :
    VariantType(EHoudiniNodeVariantType::UInt32)
{
    FMemoryWriter Writer(VariantValue, true);
    Writer << Value;
}


FHoudiniNodeVariant::FHoudiniNodeVariant(uint64 Value) :
    VariantType(EHoudiniNodeVariantType::UInt64)
{
    FMemoryWriter Writer(VariantValue, true);
    Writer << Value;
}


FHoudiniNodeVariant::FHoudiniNodeVariant(const FString& Value) :
    VariantType(EHoudiniNodeVariantType::String)
{
    FString String(Value);

    FMemoryWriter Writer(VariantValue, true);
    Writer << String;
}


FHoudiniNodeVariant::FHoudiniNodeVariant(const FName& Value) :
    VariantType(EHoudiniNodeVariantType::String)
{
    FString String = Value.ToString();

    FMemoryWriter Writer(VariantValue, true);
    Writer << String;
}


FHoudiniNodeVariant::FHoudiniNodeVariant(const FVector& Value, bool bScale) :
    VariantType(EHoudiniNodeVariantType::Vector)
{
    FVector Vector = Value;
    Swap(Vector.Y, Vector.Z);

    if(bScale)
    {
        Vector /= 100.0f;
    }

    FMemoryWriter Writer(VariantValue, true);
    Writer << Vector;
}


FHoudiniNodeVariant::FHoudiniNodeVariant(const FVector2D& Value, bool bUVSwap) :
    VariantType(EHoudiniNodeVariantType::Vector2)
{
    FVector2D Vector = Value;

    if(bUVSwap)
    {
        Vector.Y = 1.0f - Vector.Y;
    }

    FMemoryWriter Writer(VariantValue, true);
    Writer << Vector;
}


FHoudiniNodeVariant::FHoudiniNodeVariant(const FVector4& Value, bool bScale) :
    VariantType(EHoudiniNodeVariantType::Vector4)
{
    FVector4 Vector = Value;
    Swap(Vector.Y, Vector.Z);

    if(bScale)
    {
        Vector.X /= 100.0f;
        Vector.Y /= 100.0f;
        Vector.Z /= 100.0f;
    }

    FMemoryWriter Writer(VariantValue, true);
    Writer << Vector;
}


FHoudiniNodeVariant::FHoudiniNodeVariant(const FQuat& Value) :
    VariantType(EHoudiniNodeVariantType::Quaternion)
{
    FQuat Quat = Value;

    Swap(Quat.Y, Quat.Z);
    Quat.W *= -1.0f;

    FMemoryWriter Writer(VariantValue, true);
    Writer << Quat;
}


FHoudiniNodeVariant::FHoudiniNodeVariant(const FRotator& Value) :
    VariantType(EHoudiniNodeVariantType::Rotator)
{
    FRotator Rotator = Value;

    Swap(Rotator.Pitch, Rotator.Yaw);

    FMemoryWriter Writer(VariantValue, true);
    Writer << Rotator;
}


FHoudiniNodeVariant::FHoudiniNodeVariant(const FTransform& Value, bool bScale) :
    VariantType(EHoudiniNodeVariantType::Transform)
{
    FVector Vector = Value.GetTranslation();
    Swap(Vector.Y, Vector.Z);

    if(bScale)
    {
        Vector /= 100.0f;
    }

    FQuat Quat = Value.GetRotation();
    Swap(Quat.Y, Quat.Z);
    Quat.W *= -1.0f;

    FVector Scale = Value.GetScale3D();
    Swap(Scale.Y, Scale.Z);

    FTransform Transform(Quat, Vector, Scale);

    FMemoryWriter Writer(VariantValue, true);
    Writer << Transform;
}


FHoudiniNodeVariant::FHoudiniNodeVariant(const FColor& Value) :
    VariantType(EHoudiniNodeVariantType::Color)
{
    FLinearColor Color(Value);

    FMemoryWriter Writer(VariantValue, true);
    Writer << Color;
}


FHoudiniNodeVariant::FHoudiniNodeVariant(const FLinearColor& Value) :
    VariantType(EHoudiniNodeVariantType::Color)
{
    FLinearColor Color(Value);

    FMemoryWriter Writer(VariantValue, true);
    Writer << Color;
}


FHoudiniNodeVariant::FHoudiniNodeVariant(const FBox& Value, bool bScale) :
    VariantType(EHoudiniNodeVariantType::Box)
{
    FBox Box(Value);
    Swap(Box.Min.Y, Box.Min.Z);
    Swap(Box.Max.Y, Box.Max.Z);

    if(bScale)
    {
        Box.Min /= 100.0f;
        Box.Max /= 100.0f;
    }

    FMemoryWriter Writer(VariantValue, true);
    Writer << Box;
}


FHoudiniNodeVariant::FHoudiniNodeVariant(const FBoxSphereBounds& Value, bool bScale) :
    VariantType(EHoudiniNodeVariantType::BoxSphereBounds)
{
    FBoxSphereBounds Bounds(Value);
    Swap(Bounds.Origin.Y, Bounds.Origin.Z);
    Swap(Bounds.BoxExtent.Y, Bounds.BoxExtent.Z);

    if(bScale)
    {
        Bounds.Origin /= 100.0f;
        Bounds.BoxExtent /= 100.0f;
    }

    FMemoryWriter Writer(VariantValue, true);
    Writer << Bounds;
}


FHoudiniNodeVariant::FHoudiniNodeVariant(const TArray<FHoudiniNodeVariant>& Value) :
    VariantType(EHoudiniNodeVariantType::Array)
{
    TArray<FHoudiniNodeVariant> Array(Value);

    FMemoryWriter Writer(VariantValue, true);
    Writer << Array;
}


FHoudiniNodeVariant::FHoudiniNodeVariant(const TMap<FString, FHoudiniNodeVariant>& Value) :
    VariantType(EHoudiniNodeVariantType::Map)
{
    TMap<FString, FHoudiniNodeVariant> Map(Value);

    FMemoryWriter Writer(VariantValue, true);
    Writer << Map;
}


EHoudiniNodeVariantType::Enum
FHoudiniNodeVariant::GetType() const
{
    return VariantType;
}


bool
FHoudiniNodeVariant::IsNull() const
{
    return VariantType == EHoudiniNodeVariantType::Null;
}


bool
FHoudiniNodeVariant::IsObject() const
{
    return VariantType == EHoudiniNodeVariantType::Object;
}


bool
FHoudiniNodeVariant::IsArray() const
{
    return VariantType == EHoudiniNodeVariantType::Array;
}


bool
FHoudiniNodeVariant::IsMap() const
{
    return VariantType == EHoudiniNodeVariantType::Map;
}


bool
FHoudiniNodeVariant::IsContainer() const
{
    if(IsArray() || IsMap())
    {
        return true;
    }

    return false;
}


void
FHoudiniNodeVariant::Pack(TArray<uint8>& PackedBuffer) const
{
    TArray<uint8> SerializedBytes;
    FMemoryWriter Writer(SerializedBytes, true);
    Writer.SetByteSwapping(true);

    Pack(Writer);

    PackedBuffer.Append(SerializedBytes);
}


void
FHoudiniNodeVariant::Pack(FMemoryWriter& Writer) const
{
    FMemoryReader Reader(VariantValue, true);

    switch(VariantType)
    {
        default:
        case EHoudiniNodeVariantType::Null:
        {
            uint8 Code = 0xC0;
            Writer << Code;

            break;
        }

        case EHoudiniNodeVariantType::Bool:
        {
            bool bResult = false;
            Reader << bResult;

            if(bResult)
            {
                uint8 Code = 0xC3;
                Writer << Code;
            }
            else
            {
                uint8 Code = 0xC2;
                Writer << Code;
            }

            break;
        }

        case EHoudiniNodeVariantType::Int8:
        {
            int8 Value = 0;
            Reader << Value;

            Pack((int64) Value, Writer);
            break;
        }

        case EHoudiniNodeVariantType::Int16:
        {
            int16 Value = 0;
            Reader << Value;

            Pack((int64) Value, Writer);
            break;
        }

        case EHoudiniNodeVariantType::Int32:
        {
            int32 Value = 0;
            Reader << Value;

            Pack((int64) Value, Writer);
            break;
        }

        case EHoudiniNodeVariantType::Int64:
        {
            int64 Value = 0;
            Reader << Value;

            Pack((int64) Value, Writer);
            break;
        }

        case EHoudiniNodeVariantType::UInt8:
        {
            uint8 Value = 0u;
            Reader << Value;

            Pack((uint64) Value, Writer);
            break;
        }

        case EHoudiniNodeVariantType::UInt16:
        {
            uint16 Value = 0u;
            Reader << Value;

            Pack((uint64) Value, Writer);
            break;
        }

        case EHoudiniNodeVariantType::UInt32:
        {
            uint32 Value = 0u;
            Reader << Value;

            Pack((uint64) Value, Writer);
            break;
        }

        case EHoudiniNodeVariantType::UInt64:
        {
            uint64 Value = 0u;
            Reader << Value;

            Pack((uint64) Value, Writer);
            break;
        }

        case EHoudiniNodeVariantType::Float:
        {
            float Value = 0.0f;
            Reader << Value;

            uint8 Code = 0xCA;
            Writer << Code << Value;

            break;
        }

        case EHoudiniNodeVariantType::Double:
        {
            double Value = 0.0;
            Reader << Value;

            uint8 Code = 0xCB;
            Writer << Code << Value;

            break;
        }

        case EHoudiniNodeVariantType::String:
        {
            FString String(TEXT(""));
            Reader << String;

            Pack(String, Writer);
            break;
        }

        case EHoudiniNodeVariantType::Vector:
        {
            FVector Value = FVector::ZeroVector;
            Reader << Value;

            uint8 Code = 0x93;
            Writer << Code << Value.X << Value.Y << Value.Z;

            break;
        }

        case EHoudiniNodeVariantType::Vector2:
        {
            FVector2D Value = FVector2D::ZeroVector;
            Reader << Value;

            uint8 Code = 0x92;
            Writer << Code << Value.X << Value.Y;

            break;
        }

        case EHoudiniNodeVariantType::Vector4:
        {
            FVector4 Value(0.0f, 0.0f, 0.0f, 1.0f);
            Reader << Value;

            uint8 Code = 0x94;
            Writer << Code << Value.X << Value.Y << Value.Z << Value.W;

            break;
        }

        case EHoudiniNodeVariantType::Quaternion:
        {
            FQuat Value = FQuat::Identity;
            Reader << Value;

            uint8 Code = 0x94;
            Writer << Code << Value.X << Value.Y << Value.Z << Value.W;

            break;
        }

        case EHoudiniNodeVariantType::Rotator:
        {
            FRotator Value = FRotator::ZeroRotator;
            Reader << Value;

            uint8 Code = 0x93;
            Writer << Code << Value.Pitch << Value.Yaw << Value.Roll;

            break;
        }

        case EHoudiniNodeVariantType::Transform:
        {
            FTransform Transform = FTransform::Identity;
            Reader << Transform;

            uint8 CodeTransform = 0x93;
            Writer << CodeTransform;

            {
                FVector Translation = Transform.GetTranslation();

                uint8 Code = 0x93;
                Writer << Code << Translation.X << Translation.Y << Translation.Z;
            }

            {
                FQuat Rotation = Transform.GetRotation();

                uint8 Code = 0x94;
                Writer << Code << Rotation.X << Rotation.Y << Rotation.Z << Rotation.W;
            }

            {
                FVector Scale = Transform.GetScale3D();

                uint8 Code = 0x93;
                Writer << Code << Scale.X << Scale.Y << Scale.Z;
            }
        }

        case EHoudiniNodeVariantType::Color:
        {
            FLinearColor Color = FLinearColor::White;
            Reader << Color;

            uint8 Code = 0x94;
            Writer << Code << Color.R << Color.G << Color.B;

            break;
        }

        case EHoudiniNodeVariantType::Object:
        {
            // Implementation missing.

            break;
        }

        case EHoudiniNodeVariantType::Box:
        {
            FBox Box;
            Reader << Box;

            uint8 CodeBox = 0x92;
            Writer << CodeBox;

            {
                uint8 Code = 0x93;
                Writer << Code << Box.Min.X << Box.Min.Y << Box.Min.Z;
            }

            {
                uint8 Code = 0x93;
                Writer << Code << Box.Max.X << Box.Max.Y << Box.Max.Z;
            }

            break;
        }

        case EHoudiniNodeVariantType::BoxSphereBounds:
        {
            FBoxSphereBounds Bounds;
            Reader << Bounds;

            uint8 CodeBounds = 0x93;
            Writer << CodeBounds;

            {
                uint8 Code = 0x93;
                Writer << Code << Bounds.Origin.X << Bounds.Origin << Bounds.Origin.Z;
            }

            {
                uint8 Code = 0x93;
                Writer << Code << Bounds.BoxExtent.X << Bounds.BoxExtent.Y << Bounds.BoxExtent.Z;
            }

            Writer << Bounds.SphereRadius;

            break;
        }

        case EHoudiniNodeVariantType::Array:
        {
            TArray<FHoudiniNodeVariant> Array;
            Reader << Array;

            const int32 ArraySize = Array.Num();

            if(ArraySize > 0)
            {
                uint8 Code = 0;

                if(ArraySize < 16)
                {
                    Code = 0x90 | ArraySize;
                }
                else if(ArraySize < 65536)
                {
                    Code = 0xDC;
                }
                else
                {
                    Code = 0XDD;
                }

                Writer << Code;

                for(int32 ArrayIdx = 0; ArrayIdx < ArraySize; ++ArrayIdx)
                {
                    const FHoudiniNodeVariant& Variant = Array[ArrayIdx];
                    Variant.Pack(Writer);
                }
            }
            else
            {
                uint8 Code = 0xC0;
                Writer << Code;
            }

            break;
        }

        case EHoudiniNodeVariantType::Map:
        {
            TMap<FString, FHoudiniNodeVariant> Map;
            Reader << Map;

            const int32 MapSize = Map.Num();

            if(MapSize > 0)
            {
                uint8 Code = 0;

                if(MapSize < 16)
                {
                    Code = 0x80 | MapSize;
                }
                else if(MapSize < 65536)
                {
                    Code = 0xDE;
                }
                else
                {
                    Code = 0XDF;
                }

                Writer << Code;

                for(TMap<FString, FHoudiniNodeVariant>::TIterator Iter(Map); Iter; ++Iter)
                {
                    const FString& String = Iter.Key();
                    const FHoudiniNodeVariant& Variant = Iter.Value();

                    Pack(String, Writer);
                    Variant.Pack(Writer);
                }
            }
            else
            {
                uint8 Code = 0xC0;
                Writer << Code;
            }

            break;
        }
    }
}


void
FHoudiniNodeVariant::Pack(int64 Value, FMemoryWriter& Writer) const
{
    if(Value >= 0)
    {
        Pack((uint64) Value, Writer);
    }
    else
    {
        if(Value >= -32)
        {
            int8 ValueCast = (int8) Value;
            Writer << ValueCast;
        }
        else if(Value >= -128)
        {
            uint8 Code = 0xD0;
            int8 ValueCast = (int8) Value;

            Writer << Code << ValueCast;
        }
        else if(Value >= -32768)
        {
            uint8 Code = 0xD1;
            int16 ValueCast = (int16) Value;

            Writer << Code << ValueCast;
        }
        else if(Value >= -2147483648LL)
        {
            uint8 Code = 0xD2;
            int32 ValueCast = (int32) Value;

            Writer << Code << ValueCast;
        }
        else
        {
            uint8 Code = 0xD3;
            Writer << Code << Value;
        }
    }
}


void
FHoudiniNodeVariant::Pack(uint64 Value, FMemoryWriter& Writer) const
{
    if(Value < 128u)
    {
        uint8 ValueCast = (uint8) Value;
        Writer << ValueCast;
    }
    else if(Value < 256u)
    {
        uint8 Code = 0xCC;
        uint8 ValueCast = (uint8) Value;

        Writer << Code << ValueCast;
    }
    else if(Value < 65536u)
    {
        uint8 Code = 0xCD;
        uint16 ValueCast = (uint16) Value;

        Writer << Code << ValueCast;
    }
    else if(Value < 4294967296uLL)
    {
        uint8 Code = 0xCE;
        uint32 ValueCast = (uint32) Value;

        Writer << Code << ValueCast;
    }
    else
    {
        uint8 Code = 0xCF;
        Writer << Code << Value;
    }
}


void
FHoudiniNodeVariant::Pack(const FString& String, FMemoryWriter& Writer) const
{
    std::string Value = TCHAR_TO_UTF8(*String);
    const int32 ValueSize = Value.size();

    if(ValueSize > 0)
    {
        if(ValueSize < 32)
        {
            uint8 Code = 0xA0 | ValueSize;
        }
        else if(ValueSize < 256)
        {
            uint8 Code = 0xD9;
        }
        else if(ValueSize < 65536)
        {
            uint8 Code = 0xDA;
        }
        else
        {
            uint8 Code = 0xDB;
        }

        Writer.Serialize(&Value[0], ValueSize);
    }
    else
    {
        uint8 Code = 0xC0;
        Writer << Code;
    }
}


void
FHoudiniNodeVariant::CollectObjects(TMap<FString, FHoudiniNodeVariant>& Objects) const
{
    FMemoryReader Reader(VariantValue, true);

    if(IsObject())
    {
        UObject* Object = nullptr;
        Reader << Object;

        if(Object)
        {
            const FString& ObjectPath = Object->GetPathName();
            Objects.Add(ObjectPath, this);
        }
    }
    else if(IsArray())
    {
        TArray<FHoudiniNodeVariant> Array;
        Reader << Array;

        const int32 ArraySize = Array.Num();
        for(int32 Idx = 0; Idx < ArraySize; ++Idx)
        {
            const FHoudiniNodeVariant& Variant = Array[Idx];
            Variant.CollectObjects(Objects);
        }
    }
    else if(IsMap())
    {
        TMap<FString, FHoudiniNodeVariant> Map;
        Reader << Map;

        for(TMap<FString, FHoudiniNodeVariant>::TIterator Iter(Map); Iter; ++Iter)
        {
            const FHoudiniNodeVariant& Variant = Iter.Value();
            Variant.CollectObjects(Objects);
        }
    }
}


bool
FHoudiniNodeVariant::ReplaceWithReference()
{
    if(!IsObject())
    {
        return false;
    }

    FMemoryReader Reader(VariantValue, true);

    UObject* Object = nullptr;
    Reader << Object;

    if(Object && !Object->IsA(AActor::StaticClass()))
    {
        VariantType = EHoudiniNodeVariantType::String;
        FString String = Object->GetPathName();

        VariantValue.Empty();

        FMemoryWriter Writer(VariantValue, true);
        Writer << String;

        return true;
    }

    return false;
}
