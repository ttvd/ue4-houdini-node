#pragma once
#include "HoudiniNodeAsset.generated.h"


UCLASS()
class HOUDININODE_API UHoudiniNodeAsset : public UObject
{
    GENERATED_UCLASS_BODY()

public:

#if WITH_EDITORONLY_DATA

    UPROPERTY(Category=ImportSettings, VisibleAnywhere, Instanced)
    UAssetImportData* AssetImportData;

#endif
};
