#pragma once
#include "HoudiniNodeAsset.generated.h"


UCLASS()
class HOUDININODE_API UHoudiniNodeAsset : public UObject
{
    GENERATED_UCLASS_BODY()

public:

    //! Return the filename for this asset.
    bool GetFilename(UT_String& RawFilename) const;

public:

#if WITH_EDITORONLY_DATA

    UPROPERTY(Category=ImportSettings, VisibleAnywhere, Instanced)
    UAssetImportData* AssetImportData;

#endif

};
