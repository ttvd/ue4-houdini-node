#pragma once
#include "HoudiniNodeVariant.h"
#include "HoudiniNodeObjectPacker.generated.h"


class UClass;


UCLASS(abstract)
class HOUDININODE_API UHoudiniNodeObjectPacker : public UObject
{
    GENERATED_UCLASS_BODY()

public:

    //! Get supported class.
    UClass* GetSupportedClass() const;

public:

    //! Pack the object of this type.
    virtual bool Encode(TMap<FString, FHoudiniNodeVariant>& ObjectMap, UObject* Object) const;

protected:

    //! Supported class.
    UClass* SupportedClass;
};
