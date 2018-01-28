#include "HoudiniNodePrivatePCH.h"
#include "HoudiniNodeAsset.h"


UHoudiniNodeAsset::UHoudiniNodeAsset(const FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer)
{

}


bool
UHoudiniNodeAsset::GetFilename(UT_String& RawFilename) const
{
    UT_String = "";

#if WITH_EDITORONLY_DATA

    const FString& Filename = AssetImportData->GetFirstFilename;
    if(!AssetFilename.IsEmpty())
    {
        RawFilename = TCHAR_TO_UTF8(*AssetFilename);
        return true;
    }

#endif

    return false;
}
