#include "HoudiniNodeObjectPacker.h"
#include "HoudiniNodePrivatePCH.h"


UHoudiniNodeObjectPacker::UHoudiniNodeObjectPacker(const FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer),
    SupportedClass(nullptr)
{

}


UClass*
UHoudiniNodeObjectPacker::GetSupportedClass() const
{
    return SupportedClass;
}


bool
UHoudiniNodeObjectPacker::Encode(UObject* Object, TMap<FString, FHoudiniNodeVariant>& ObjectMap) const
{
    if(!Object)
    {
        return false;
    }

    return true;
}
