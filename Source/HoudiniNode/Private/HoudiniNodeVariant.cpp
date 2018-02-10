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
FHoudiniNodeVariant::IsContainer() const
{
    if(VariantType == EHoudiniNodeVariantType::Array || VariantType == EHoudiniNodeVariantType::Map)
    {
        return true;
    }

    return false;
}
