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
UHoudiniNodePropertyButton::Press()
{
    if(!Property || !Component)
    {
        return false;
    }

    const uint32 Offset = GetPropertyOffset();
    const int32 Value = 1;

    UHoudiniNodeClass* NodeClass = Cast<UHoudiniNodeClass>(Component->GetClass());
    NodeClass->OnParameterChanged(this);

    /*
    Component->PreEditChange(this);

    Component->SetScratchSpaceValueAtOffset(Value, Offset);

    FPropertyChangedEvent PropertyChangedEvent(this);
    Component->PostEditChangeProperty(PropertyChangedEvent);
    */

    return true;
}
