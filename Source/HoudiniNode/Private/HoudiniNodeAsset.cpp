#include "HoudiniNodeAsset.h"
#include "HoudiniNodePrivatePCH.h"


#if WITH_EDITOR
#include "EditorFramework/AssetImportData.h"
#endif


UHoudiniNodeAsset::UHoudiniNodeAsset(const FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer),
    AssetImportData(nullptr)
{

}


bool
UHoudiniNodeAsset::GetFilename(FString& RawFilename) const
{
    RawFilename = TEXT("");

#if WITH_EDITORONLY_DATA

    RawFilename = AssetImportData->GetFirstFilename();
    if(!RawFilename.IsEmpty())
    {
        RawFilename.ReplaceInline(TEXT("/"), TEXT("\\"));
        return true;
    }

#endif

    return false;
}
