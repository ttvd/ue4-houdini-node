#pragma once
#include "HoudiniNodeAttribute.h"


class GA_Primitive;
class UObject;


class HOUDININODE_API FHoudiniNodeAttributeVertex : public FHoudiniNodeAttribute
{
public:

    //! Create a vertex attribute object for a given detail with a given name.
    FHoudiniNodeAttributeVertex(const FHoudiniNodeDetail& InDetail, const FString& InName);

public:

    //! Given a list of primitives return vector values.
    bool Get(const TArray<GA_Primitive*>& Primitives, bool bScale, TArray<FVector>& Values) const;

    //! Given a list of primitives return color values.
    bool Get(const TArray<GA_Primitive*>& Primitives, TArray<FColor>& Values) const;
    bool Get(const TArray<GA_Primitive*>& Primitives, TArray<FLinearColor>& Values) const;
};

