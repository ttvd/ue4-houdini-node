#pragma once
#include "HoudiniNodeAsset.generated.h"


class UAssetImportData;
class FString;


UCLASS()
class HOUDININODE_API UHoudiniNodeAsset : public UObject
{
    GENERATED_UCLASS_BODY()

public:

    //! Return the filename for this asset.
    bool GetFilename(FString& RawFilename) const;

public:

#if WITH_EDITORONLY_DATA

    UPROPERTY(Category=ImportSettings, VisibleAnywhere, Instanced)
    UAssetImportData* AssetImportData;

#endif

};
