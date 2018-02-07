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

    InitializeProperty(this, Component, Template, EHoudiniNodePropertyType::Float);

    if(!ConstructProperty<float>(Node, Time, true, true))
    {
        return false;
    }

    return true;
}


bool
UHoudiniNodePropertyFloat::Update(OP_Node* Node, float Time)
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
UHoudiniNodePropertyFloat::Upload(OP_Node* Node, float Time)
{
    if(!Template || !Node || !Component || !Property)
    {
        return false;
    }

    return UploadValues(Node, Component, Time);
}

