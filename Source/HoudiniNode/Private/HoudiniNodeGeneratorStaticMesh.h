#pragma once
#include "HoudiniNodeGenerator.h"
#include "HoudiniNodeGeneratorStaticMesh.generated.h"


class UStaticMesh;
class AStaticMeshActor;

class GA_Primitive;


UCLASS()
class HOUDININODE_API UHoudiniNodeGeneratorStaticMesh : public UHoudiniNodeGenerator
{
    GENERATED_UCLASS_BODY()

public:

    //! Invoke generator on the given node. Return true if objects were generated.
    virtual bool Generate(UHoudiniNodeClass* NodeClass, TArray<AActor*>& GeneratedActors) override;

public:

    //! Return true if generator name matches a given string.
    virtual bool MatchName(const FString& InGeneratorName) const override;

protected:

    //! Create a static mesh actor for a given primitive set.
    AStaticMeshActor* CreateStaticMeshActor(UHoudiniNodeClass* NodeClass, const TArray<GA_Primitive*>& Primitives) const;

    //! Create a static mesh from a given primitive set.
    UStaticMesh* CreateStaticMesh(UHoudiniNodeClass* NodeClass, UObject* Outer, const TArray<GA_Primitive*>& Primitives) const;
};
