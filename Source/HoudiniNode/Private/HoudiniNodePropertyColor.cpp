#include "HoudiniNodePropertyColor.h"
#include "HoudiniNodeComponent.h"
#include "HoudiniNodePrivatePCH.h"


UHoudiniNodePropertyColor::UHoudiniNodePropertyColor(const FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer)
{

}


UHoudiniNodePropertyColor::~UHoudiniNodePropertyColor()
{

}


bool
UHoudiniNodePropertyColor::Construct(OP_Node* Node, const PRM_Template* Template, UHoudiniNodeComponent* Component, float Time)
{
    if(!Template || !Node || !Component)
    {
        return false;
    }

    InitializeProperty(this, Component, Template, EHoudiniNodePropertyType::Float);

    if(!ConstructProperty<float>(Node, Time, true, true))
    {
        return false;
    }

    return true;
}


bool
UHoudiniNodePropertyColor::Update(OP_Node* Node, float Time)
{
    if(!Template || !Node || !Component)
    {
        return false;
    }

    if(!ConstructProperty<float>(Node, Time, true, false))
    {
        return false;
    }

    return true;
}


bool
UHoudiniNodePropertyColor::Upload(OP_Node* Node, float Time)
{
    if(!Template || !Node || !Component || !Property)
    {
        return false;
    }

    return UploadValues(Node, Component, Time);
}

