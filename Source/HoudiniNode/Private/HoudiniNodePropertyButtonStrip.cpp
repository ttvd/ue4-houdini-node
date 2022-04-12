#include "HoudiniNodePropertyButtonStrip.h"
#include "HoudiniNodeComponent.h"
#include "HoudiniNodeClass.h"
#include "HoudiniNodePrivatePCH.h"


UHoudiniNodePropertyButtonStrip::UHoudiniNodePropertyButtonStrip(const FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer)
{

}


UHoudiniNodePropertyButtonStrip::~UHoudiniNodePropertyButtonStrip()
{

}


bool
UHoudiniNodePropertyButtonStrip::GetButtonNames(TArray<FString>& ButtonNames) const
{
    ButtonNames.Empty();

    TArray<TPair<FString, int64> > ChoiceValues;
    if(!GetChoiceValues(ChoiceValues))
    {
        return false;
    }

    for(int32 Idx = 0; Idx < ChoiceValues.Num(); ++Idx)
    {
        const TPair<FString, int64>& ChoiceValue = ChoiceValues[Idx];
        const FString& ChoiceValueString = ChoiceValue.Key;

        ButtonNames.Add(ChoiceValueString);
    }

    return ButtonNames.Num() > 0;
}
