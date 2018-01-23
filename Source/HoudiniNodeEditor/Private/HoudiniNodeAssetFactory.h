#pragma once
#include "HoudiniNodeAssetFactory.generated.h"


class UClass;
class UObject;
class FFeedbackContext;


UCLASS(config=Editor)
class UHoudiniNodeAssetFactory : public UFactory
{
    GENERATED_UCLASS_BODY()

private:

    virtual bool DoesSupportClass(UClass* Class) override;
    virtual FText GetDisplayName() const override;

private:

    virtual UObject* FactoryCreateBinary(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
        UObject* Context, const TCHAR* Type, const uint8*& Buffer, const uint8* BufferEnd,
        FFeedbackContext* Warn) override;
};
