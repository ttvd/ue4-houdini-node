#include "HoudiniNodePropertyString.h"
#include "HoudiniNodeComponent.h"
#include "HoudiniNodePrivatePCH.h"


UHoudiniNodePropertyString::UHoudiniNodePropertyString(const FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer)
{

}


UHoudiniNodePropertyString::~UHoudiniNodePropertyString()
{

}


bool
UHoudiniNodePropertyString::Construct(OP_Node* Node, const PRM_Template* Template, UHoudiniNodeComponent* Component, float Time)
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
UHoudiniNodePropertyString::Update(OP_Node* Node, float Time)
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
UHoudiniNodePropertyString::Upload(OP_Node* Node, float Time)
{
    if(!Template || !Node || !Component || !Property)
    {
        return false;
    }

    return UploadValues(Node, Component, Time);
}

