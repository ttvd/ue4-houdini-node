#include "HoudiniNodePropertyInt.h"
#include "HoudiniNodeComponent.h"
#include "HoudiniNodePrivatePCH.h"


UHoudiniNodePropertyInt::UHoudiniNodePropertyInt(const FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer)
{

}


UHoudiniNodePropertyInt::~UHoudiniNodePropertyInt()
{

}


bool
UHoudiniNodePropertyInt::Construct(OP_Node* Node, const PRM_Template* Template, UHoudiniNodeComponent* Component, float Time)
{
    if(!Template || !Node || !Component)
    {
        return false;
    }

    InitializeProperty(this, Component, Template);

    if(!ConstructProperty<int32>(Node, Time, true, true))
    {
        return false;
    }

    return true;
}


bool
UHoudiniNodePropertyInt::Update(OP_Node* Node, float Time)
{
    if(!Template || !Node || !Component)
    {
        return false;
    }

    if(!ConstructProperty<int32>(Node, Time, true, false))
    {
        return false;
    }

    return true;
}

