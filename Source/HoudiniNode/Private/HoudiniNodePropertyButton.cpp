#include "HoudiniNodePropertyButton.h"
#include "HoudiniNodeComponent.h"
#include "HoudiniNodePrivatePCH.h"


UHoudiniNodePropertyButton::UHoudiniNodePropertyButton(const FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer)
{

}


UHoudiniNodePropertyButton::~UHoudiniNodePropertyButton()
{

}


bool
UHoudiniNodePropertyButton::Construct(OP_Node* Node, const PRM_Template* Template, UHoudiniNodeComponent* Component, float Time)
{
    if(!Template || !Node || !Component)
    {
        return false;
    }

    InitializeProperty(this, Component, Template, EHoudiniNodePropertyType::Integer);

    if(!ConstructProperty<int32>(Node, Time, true, true))
    {
        return false;
    }

    return true;
}


bool
UHoudiniNodePropertyButton::Update(OP_Node* Node, float Time)
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


bool
UHoudiniNodePropertyButton::Upload(OP_Node* Node, float Time)
{
    if(!Template || !Node || !Component || !Property)
    {
        return false;
    }

    return UploadValues(Node, Component, Time);
}
