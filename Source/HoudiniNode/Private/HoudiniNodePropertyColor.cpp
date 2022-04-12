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
UHoudiniNodePropertyColor::Construct(const PRM_Template* Template, UHoudiniNodeComponent* Component)
{
    if(!Template || !Component)
    {
        return false;
    }

    InitializeProperty(this, Component, Template, EHoudiniNodePropertyType::Float);

    if(!ConstructProperty<float>(true, true))
    {
        return false;
    }

    return true;
}


bool
UHoudiniNodePropertyColor::Update()
{
    if(!Template || !Component)
    {
        return false;
    }

    if(!ConstructProperty<float>(true, false))
    {
        return false;
    }

    return true;
}


bool
UHoudiniNodePropertyColor::Upload()
{
    if(!Template || !Component || !Property)
    {
        return false;
    }

    return UploadValues();
}

