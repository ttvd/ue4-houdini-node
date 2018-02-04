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

    //! Invoke generator on the given Node. Return true if objects were generated.
    virtual bool Generate(UHoudiniNodeClass* NodeClass, TArray<AActor*>& GeneratedActors) override;

protected:

    //! Create a static mesh actor for a given part and primitive set.
    AStaticMeshActor* CreateStaticMeshActor(UHoudiniNodeClass* NodeClass, const TArray<GA_Primitive*>& Primitives) const;

    //! Create a static mesh.
    UStaticMesh* CreateStaticMesh(UHoudiniNodeClass* NodeClass, UObject* Outer, const TArray<GA_Primitive*>& Primitives) const;
};

