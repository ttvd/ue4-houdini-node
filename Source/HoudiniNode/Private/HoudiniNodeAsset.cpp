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
UHoudiniNodeAsset::GetFilename(UT_String& RawFilename) const
{
    RawFilename = "";

#if WITH_EDITORONLY_DATA

    const FString& AssetFilename = AssetImportData->GetFirstFilename();
    if(!AssetFilename.IsEmpty())
    {
        RawFilename = TCHAR_TO_UTF8(*AssetFilename);
        return true;
    }

#endif

    return false;
}
