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


    return true;
}
