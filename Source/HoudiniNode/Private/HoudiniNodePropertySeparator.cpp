#include "HoudiniNodePropertySeparator.h"
#include "HoudiniNodeComponent.h"
#include "HoudiniNodePrivatePCH.h"


UHoudiniNodePropertySeparator::UHoudiniNodePropertySeparator(const FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer)
{

}


UHoudiniNodePropertySeparator::~UHoudiniNodePropertySeparator()
{

}


bool
UHoudiniNodePropertySeparator::Construct(OP_Node* Node, const PRM_Template* Template, UHoudiniNodeComponent* Component, float Time)
{
    if(!Template || !Node || !Component)
    {
        return false;
    }

    InitializeProperty(this, Component, Template, EHoudiniNodePropertyType::String);

    if(!ConstructProperty<FString>(Node, Time, true, true))
    {
        return false;
    }

    return true;
}


bool
UHoudiniNodePropertySeparator::Update(OP_Node* Node, float Time)
{
    if(!Template || !Node || !Component)
    {
        return false;
    }

    if(!ConstructProperty<FString>(Node, Time, true, false))
    {
        return false;
    }

    return true;
}


bool
UHoudiniNodePropertySeparator::Upload(OP_Node* Node, float Time)
{
    if(!Template || !Node || !Component || !Property)
    {
        return false;
    }

    return UploadValues(Node, Component, Time);
}

