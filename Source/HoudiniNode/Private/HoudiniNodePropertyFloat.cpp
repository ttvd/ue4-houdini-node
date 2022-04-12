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
UHoudiniNodePropertyFloat::Construct(const PRM_Template* Template, UHoudiniNodeComponent* Component)
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
UHoudiniNodePropertyFloat::Update()
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
UHoudiniNodePropertyFloat::Upload()
{
    if(!Template || !Component || !Property)
    {
        return false;
    }

    return UploadValues();
}

