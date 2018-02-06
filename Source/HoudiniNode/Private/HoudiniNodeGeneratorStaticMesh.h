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

protected:

    //! Given a list of primitives, return vertex normals.
    bool GetVertexNormals(UHoudiniNodeClass* NodeClass, const TArray<GA_Primitive*>& Primitives, uint32 VertexCount,
        TArray<FVector>& Normals) const;

    //! Given a list of primitives, return vertex colors.
    bool GetVertexColors(UHoudiniNodeClass* NodeClass, const TArray<GA_Primitive*>& Primitives, uint32 VertexCount,
        TArray<FColor>& Colors) const;

    //! Given a list of primitives, return uvs.
    bool GetVertexUVs(UHoudiniNodeClass* NodeClass, const TArray<GA_Primitive*>& Primitives, uint32 VertexCount,
        uint32 Channel, TArray<FVector2D>& UVs) const;

protected:

    //! Patch the winding order.
    template <typename TType> bool PatchVertexWindingOrder(TArray<TType>& Array) const;
};


template <typename TType>
bool
UHoudiniNodeGeneratorStaticMesh::PatchVertexWindingOrder(TArray<TType>& Array) const
{
    const int32 VertexCount = Array.Num();
    if(VertexCount % 3 != 0)
    {
        return false;
    }

    const int32 PrimitiveCount = VertexCount / 3;

    for(int32 Idx = 0; Idx < PrimitiveCount; ++Idx)
    {
        TType& Vertex0 = Array[Idx * 3 + 0];
        TType& Vertex1 = Array[Idx * 3 + 1];
        TType& Vertex2 = Array[Idx * 3 + 2];

        Swap(Vertex1, Vertex2);
    }

    return true;
}
