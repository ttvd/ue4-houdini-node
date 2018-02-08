#include "HoudiniNodePropertyBool.h"
#include "HoudiniNodeComponent.h"
#include "HoudiniNodePrivatePCH.h"


UHoudiniNodePropertyBool::UHoudiniNodePropertyBool(const FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer)
{

}


UHoudiniNodePropertyBool::~UHoudiniNodePropertyBool()
{

}


bool
UHoudiniNodePropertyBool::Construct(const PRM_Template* Template, UHoudiniNodeComponent* Component)
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
UHoudiniNodePropertyBool::Update()
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
UHoudiniNodePropertyBool::Upload()
{
    if(!Template || !Component || !Property)
    {
        return false;
    }

    return UploadValues(Component);
}
