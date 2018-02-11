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
