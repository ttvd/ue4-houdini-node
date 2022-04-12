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
UHoudiniNodePropertyString::Construct(const PRM_Template* Template, UHoudiniNodeComponent* Component)
{
    if(!Template || !Component)
    {
        return false;
    }

    InitializeProperty(this, Component, Template, EHoudiniNodePropertyType::String);

    if(!ConstructProperty<FString>(true, true))
    {
        return false;
    }

    return true;
}


bool
UHoudiniNodePropertyString::Update()
{
    if(!Template || !Component)
    {
        return false;
    }

    if(!ConstructProperty<FString>(true, false))
    {
        return false;
    }

    return true;
}


bool
UHoudiniNodePropertyString::Upload()
{
    if(!Template || !Component || !Property)
    {
        return false;
    }

    return UploadValues();
}

