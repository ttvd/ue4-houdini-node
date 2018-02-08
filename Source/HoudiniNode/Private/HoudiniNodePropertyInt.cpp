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
UHoudiniNodePropertyInt::Construct(const PRM_Template* Template, UHoudiniNodeComponent* Component)
{
    if(!Template || !Component)
    {
        return false;
    }

    InitializeProperty(this, Component, Template, EHoudiniNodePropertyType::Integer);

    if(!ConstructProperty<int32>(true, true))
    {
        return false;
    }

    return true;
}


bool
UHoudiniNodePropertyInt::Update()
{
    if(!Template || !Component)
    {
        return false;
    }

    if(!ConstructProperty<int32>(true, false))
    {
        return false;
    }

    return true;
}


bool
UHoudiniNodePropertyInt::Upload()
{
    if(!Template || !Component || !Property)
    {
        return false;
    }

    return UploadValues();
}
