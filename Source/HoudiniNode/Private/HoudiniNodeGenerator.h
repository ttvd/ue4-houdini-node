#pragma once
#include "HoudiniNodeGenerator.generated.h"

class UHoudiniNodeClass;


UCLASS(abstract)
class HOUDININODE_API UHoudiniNodeGenerator : public UObject
{
    GENERATED_UCLASS_BODY()

public:

    //! Invoke generator on the given Node. Return true if objects were generated.
    virtual bool Generate(UHoudiniNodeClass* NodeClass, TArray<AActor*>& GeneratedActors);

public:

    //! Return true if this generator supports a given class.
    virtual bool DoesSupportClass(UClass* Class) const;

    //! Return true if this generator supports a given object.
    virtual bool DoesSupport(UObject* Object) const;

public:

    // Invoked before generator is used.
    virtual void Prepare();

    //! Invoked after generator is used.
    virtual void CleanUp();

public:

    //! Discard a given object, return true if object is supported and discarded.
    virtual bool Discard(UObject* Object) const;

    //! Discard a list of objects, return true if at least one object is discarded.
    virtual bool Discard(const TArray<UObject*>& Objects) const;

public:

    //! Return the list of supported classes by this generator.
    const TArray<UClass*>& GetSupportedClasses() const;

    //! Return the name of this generator.
    const FString& GetGeneratorName() const;

protected:

    //! List of supported classes by this generator.
    TArray<UClass*> SupportedClasses;

    //! Name of this generator.
    FString GeneratorName;
};
