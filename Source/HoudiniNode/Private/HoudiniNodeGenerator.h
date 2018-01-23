#pragma once
#include "HoudiniNodeGenerator.generated.h"


UCLASS(abstract)
class HOUDININODE_API UHoudiniNodeGenerator : public UObject
{
    GENERATED_UCLASS_BODY()

public:

    virtual bool DoesSupportClass(UClass* Class) const;
    virtual bool DoesSupport(UObject* Object) const;

public:

    virtual void Prepare();
    virtual void CleanUp();

public:

    virtual bool Discard(UObject* Object) const;
    virtual bool Discard(TArray<UObject*>& Objects) const;

public:

    const TArray<UClass*>& GetSupportedClasses() const;

protected:

    TArray<UClass*> SupportedClasses;
};

