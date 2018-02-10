#pragma once

namespace EHoudiniNodeVariantType
{
    enum Enum
    {
        Null = 0,

        Bool,

        Int8,
        Int16,
        Int32,
        Int64,
        UInt8,
        UInt16,
        UInt32,
        UInt64,

        Float,
        Double,

        String,

        Vector,
        Vector2,
        Vector4,
        Quaternion,
        Rotator,
        Transform,

        Color,

        Object,

        Box,
        BoxSphereBounds,

        Array,
        Map
    };
}

