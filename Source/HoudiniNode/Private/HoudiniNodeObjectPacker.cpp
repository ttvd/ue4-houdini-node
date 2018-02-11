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
UHoudiniNodeObjectPacker::Encode(TMap<FString, FHoudiniNodeVariant>& ObjectMap, UObject* Object) const
{
    if(!Object)
    {
        return false;
    }

    return true;
}
