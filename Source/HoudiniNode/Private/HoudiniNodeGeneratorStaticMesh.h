#pragma once
#include "HoudiniNodeGenerator.h"
#include "HoudiniNodeGeneratorStaticMesh.generated.h"


class UStaticMesh;


UCLASS()
class HOUDININODE_API UHoudiniNodeGeneratorStaticMesh : public UHoudiniNodeGenerator
{
    GENERATED_UCLASS_BODY()

public:

    //! Invoke generator on the given Node. Return true if objects were generated.
    virtual bool Generate(UHoudiniNodeClass* NodeClass, TArray<AActor*>& GeneratedActors) override;

protected:

    //! Create a static mesh.
    UStaticMesh* CreateStaticMesh(UHoudiniNodeClass* NodeClass, UObject* Outer) const;
};

