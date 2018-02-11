#pragma once
#include "HoudiniNodeObjectPacker.generated.h"


class UClass;


UCLASS(abstract)
class HOUDININODE_API UHoudiniNodeObjectPacker : public UObject
{
    GENERATED_UCLASS_BODY()

public:

    //! Get supported class.
    UClass* GetSupportedClass() const;

protected:

    //! Supported class.
    UClass* SupportedClass;
};
