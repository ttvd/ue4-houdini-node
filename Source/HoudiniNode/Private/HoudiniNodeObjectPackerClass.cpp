#include "HoudiniNodeObjectPackerClass.h"
#include "HoudiniNodePrivatePCH.h"


UHoudiniNodeObjectPackerClass::UHoudiniNodeObjectPackerClass(const FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer)
{
    SupportedClass = UClass::StaticClass();
}

