#include "HoudiniNodePropertyFloat.h"
#include "HoudiniNodeComponent.h"
#include "HoudiniNodePrivatePCH.h"


UHoudiniNodePropertyFloat::UHoudiniNodePropertyFloat(const FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer)
{

}


UHoudiniNodePropertyFloat::~UHoudiniNodePropertyFloat()
{

}


bool
UHoudiniNodePropertyFloat::Construct(OP_Node* Node, const PRM_Template* Template, UHoudiniNodeComponent* Component, float Time)
{
    if(!Template || !Node || !Component)
    {
        return false;
    }

    InitializeProperty(this, Component, Template);

    if(!ConstructProperty<float>(Node, Time))
    {
        return false;
    }

    return true;
}

