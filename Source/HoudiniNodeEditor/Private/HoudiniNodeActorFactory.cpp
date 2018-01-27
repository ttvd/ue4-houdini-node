#include "HoudiniNodeEditorPrivatePCH.h"
#include "HoudiniNodeActorFactory.h"
#include "HoudiniNodeAsset.h"
#include "HoudiniNodeActor.h"


UHoudiniNodeActorFactory::UHoudiniNodeActorFactory(const FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer)
{
    DisplayName = LOCTEXT("HoudiniNodeActorFactoryDisplayName", "Houdini Node Asset");
    NewActorClass = AHoudiniNodeActor::StaticClass();
}


UHoudiniNodeActorFactory::~UHoudiniNodeActorFactory()
{

}


bool
UHoudiniNodeActorFactory::CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg)
{
    if(AssetData.IsValid())
    {
        UClass* AssetClass = AssetData.GetClass();
        if(AssetClass == UHoudiniNodeAsset::StaticClass())
        {
            return true;
        }
    }

    return false;
}


UObject*
UHoudiniNodeActorFactory::GetAssetFromActorInstance(AActor* Actor)
{
    if(!Actor)
    {
        return nullptr;
    }

    AHoudiniNodeActor* HoudiniNodeActor = CastChecked<AHoudiniNodeActor>(Actor);
    if(!HoudiniNodeActor)
    {
        return nullptr;
    }

    return HoudiniNodeActor->HoudiniNodeAsset;
}


void
UHoudiniNodeActorFactory::PostSpawnActor(UObject* Asset, AActor* Actor)
{
    if(!Actor)
    {
        return;
    }

    AHoudiniNodeActor* HoudiniNodeActor = CastChecked<AHoudiniNodeActor>(Actor);
    if(!HoudiniNodeActor)
    {
        return;
    }

    UHoudiniNodeAsset* HoudiniNodeAsset = Cast<UHoudiniNodeAsset>(Asset);

    HoudiniNodeActor->PreEditChange(nullptr);
    HoudiniNodeActor->HoudiniNodeAsset = HoudiniNodeAsset;
    HoudiniNodeActor->PostEditChange();
}

