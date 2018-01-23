#include "HoudiniNodeEditorPrivatePCH.h"
#include "HoudiniNodeAssetFactory.h"
#include "HoudiniNodeAsset.h"


UHoudiniNodeAssetFactory::UHoudiniNodeAssetFactory(const FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer)
{
    SupportedClass = UHoudiniNodeAsset::StaticClass();

    bEditorImport = true;
    bText = false;

    Formats.Add(TEXT("otl;Houdini Node Asset"));
    Formats.Add(TEXT("otllc;Houdini Node Limited Commercial Asset"));
    Formats.Add(TEXT("hda;Houdini Node Asset"));
    Formats.Add(TEXT("hdalc;Houdini Node Limited Commercial Asset"));
}


bool
UHoudiniNodeAssetFactory::DoesSupportClass(UClass* Class)
{
    return Class == SupportedClass;
}


FText
UHoudiniNodeAssetFactory::GetDisplayName() const
{
    return LOCTEXT("HoudiniNodeAssetFactoryDescription", "Houdini Node Asset");
}


UObject*
UHoudiniNodeAssetFactory::FactoryCreateBinary(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
    UObject* Context, const TCHAR* Type, const uint8*& Buffer, const uint8* BufferEnd, FFeedbackContext* Warn)
{
    FEditorDelegates::OnAssetPreImport.Broadcast(this, InClass, InParent, InName, Type);

    UHoudiniNodeAsset* HoudiniNodeAsset = NewObject<UHoudiniNodeAsset>(InParent, InName, Flags);
    const FString& CurrentFilename = UFactory::GetCurrentFilename();

    {
        UAssetImportData* AssetImportData = HoudiniNodeAsset->AssetImportData;
        if(!AssetImportData)
        {
            AssetImportData = NewObject<UAssetImportData>(HoudiniNodeAsset, UAssetImportData::StaticClass());
            HoudiniNodeAsset->AssetImportData = AssetImportData;
        }

        AssetImportData->Update(CurrentFilename);
    }

    FEditorDelegates::OnAssetPostImport.Broadcast(this, HoudiniNodeAsset);

    return HoudiniNodeAsset;
}
