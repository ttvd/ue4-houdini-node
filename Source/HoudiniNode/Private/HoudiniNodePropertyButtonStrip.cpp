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

    if(!Property || !Component)
    {
        return false;
    }

    UHoudiniNodeClass* HoudiniNodeClass = Cast<UHoudiniNodeClass>(Component->GetClass());

    const float Time = HoudiniNodeClass->GetCookTime();
    OP_Node* Node = HoudiniNodeClass->GetNode();

    TArray<FString> Strings;

    if(!GetValues(Node, Component, Time, false, false, Strings))
    {
        return false;
    }

    for(int32 Idx = 0; Idx < Strings.Num(); ++Idx)
    {
        const FString& Value = Strings[Idx];
        ButtonNames.Add(Value);
    }

    return ButtonNames.Num() > 0;
}