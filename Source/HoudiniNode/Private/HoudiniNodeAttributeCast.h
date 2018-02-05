#pragma once
#include "HoudiniNodeAttribute.h"


class GA_Primitive;
class UObject;


class HOUDININODE_API FHoudiniNodeAttributeCast
{
public:

    //! Create a cast attribute object for a given detail with a given name.
    FHoudiniNodeAttributeCast(const FHoudiniNodeDetail& InDetail, const FString& InName);

public:

    //! Return true if this is a valid cast attribute.
    bool IsValid() const;

public:

    //! Retrieve vector type as vertex attribute.
    bool GetAsVertex(const TArray<GA_Primitive*>& Primitives, TArray<FVector>& Values) const;

protected:

    //! Detail.
    const FHoudiniNodeDetail& Detail;

    //! Name of the attribute.
    FString Name;
    UT_String NameRaw;
};

