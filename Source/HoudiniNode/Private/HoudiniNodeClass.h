#pragma once
#include "HoudiniNodeClass.generated.h"


UCLASS()
class HOUDININODE_API UHoudiniNodeClass : public UClass
{
    GENERATED_UCLASS_BODY()
    virtual ~UHoudiniNodeClass();

protected:

    //! List of generated properties.
    TMap<FString, UProperty*> Properties;
};
