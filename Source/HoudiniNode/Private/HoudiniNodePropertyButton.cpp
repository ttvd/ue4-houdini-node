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

    Component->PreEditChange(this);
    Component->SetScratchSpaceValueAtOffset(Value, Offset);

#if WITH_EDITOR

    FPropertyChangedEvent PropertyChangedEvent(this, EPropertyChangeType::ValueSet);
    Component->PostEditChangeProperty(PropertyChangedEvent);

#endif

    return true;
}
