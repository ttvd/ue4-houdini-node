#include "HoudiniNodePrivatePCH.h"
#include "HoudiniNodeActor.h"
#include "HoudiniNodeAsset.h"


AHoudiniNodeActor::AHoudiniNodeActor(const FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer),
    HoudiniNodeAsset(nullptr),
    Node(nullptr)
{

}


AHoudiniNodeActor::~AHoudiniNodeActor()
{

}

