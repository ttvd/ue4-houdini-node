#include "HoudiniNodeObjectPackerObject.h"
#include "HoudiniNodePrivatePCH.h"


UHoudiniNodeObjectPackerObject::UHoudiniNodeObjectPackerObject(const FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer)
{
    SupportedClass = UObject::StaticClass();
}

