#include "HoudiniNodePrivatePCH.h"
#include "HoudiniNodeClass.h"


UHoudiniNodeClass::UHoudiniNodeClass(const FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer),
    HoudiniNodeAsset(nullptr),
    Node(nullptr)
{

}


UHoudiniNodeClass::~UHoudiniNodeClass()
{

}

