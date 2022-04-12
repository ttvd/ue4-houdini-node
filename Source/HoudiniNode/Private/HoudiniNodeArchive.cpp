#include "HoudiniNodeArchive.h"
#include "HoudiniNodePrivatePCH.h"


FHoudiniNodeArchive::FHoudiniNodeArchive()
{

}


FHoudiniNodeArchive::~FHoudiniNodeArchive()
{

}


bool
FHoudiniNodeArchive::Pack(TArray<uint8>& PackedBuffer) const
{
    PackedBuffer.Empty();

    TMap<FString, FHoudiniNodeVariant> MainMap;

    // Find all objects, so that we can create an object map.
    {
        TMap<FString, FHoudiniNodeVariant> Objects;

        for(int32 VariantIdx = 0; VariantIdx < Buffer.Num(); ++VariantIdx)
        {
            const FHoudiniNodeVariant& Variant = Buffer[VariantIdx];
            Variant.CollectObjects(Objects);
        }

        FHoudiniNodeVariant ObjectMap(Objects);
        MainMap.Add(HOUDINI_NODE_PACKING_SECTION_OBJECTS, ObjectMap);
    }

    // Create the main data segment.
    {
        TArray<FHoudiniNodeVariant> Objects;

        for(int32 VariantIdx = 0; VariantIdx < Buffer.Num(); ++VariantIdx)
        {
            const FHoudiniNodeVariant& Variant = Buffer[VariantIdx];

            if(Variant.IsObject())
            {
                FHoudiniNodeVariant VariantObject(Variant);
                VariantObject.ReplaceWithReference();

                Objects.Add(VariantObject);
            }
            else
            {
                Objects.Add(Variant);
            }
        }

        FHoudiniNodeVariant ObjectArray(Objects);
        MainMap.Add(HOUDINI_NODE_PACKING_SECTION_DATA, ObjectArray);
    }

    FHoudiniNodeVariant MainMapVariant(MainMap);
    MainMapVariant.Pack(PackedBuffer);

    return true;
}
