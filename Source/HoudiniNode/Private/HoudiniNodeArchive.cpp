#include "HoudiniNodeArchive.h"
#include "HoudiniNodePrivatePCH.h"


FHoudiniNodeArchive::FHoudiniNodeArchive()
{

}


FHoudiniNodeArchive::~FHoudiniNodeArchive()
{

}


bool
FHoudiniNodeArchive::Pack(TArray<char>& PackedBuffer) const
{
    PackedBuffer.Empty();

    for(int32 VariantIdx = 0; VariantIdx < Buffer.Num(); ++VariantIdx)
    {
        const FHoudiniNodeVariant& Variant = Buffer[VariantIdx];

        if(Variant.IsNull())
        {
            
        }

    }

    return true;
}
