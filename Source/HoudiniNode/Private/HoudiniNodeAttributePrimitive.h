#pragma once
#include "HoudiniNodeAttribute.h"


class GA_Primitive;
class UObject;


class HOUDININODE_API FHoudiniNodeAttributePrimitive : public FHoudiniNodeAttribute
{
public:

    //! Create primitive attribute object for a given detail with a given name.
    FHoudiniNodeAttributePrimitive(GU_Detail* InDetail, const FString& InName);

public:

    //! Get all primitives that have this attribute set to a non-zero value.
    bool SelectNonZero(TArray<GA_Primitive*>& Prims) const;

public:

    //! Get all primitives that have this attribute set to a given integer value.
    bool Select(int32 Value, TArray<GA_Primitive*>& Prims) const;

    //! Get all primitives that have this attribute set to a given string value.
    bool Select(const FString& Value, TArray<GA_Primitive*>& Prims) const;

    //! Get all primitives that have this attribute set to a given object value.
    bool Select(UObject* Object, TArray<GA_Primitive*>& Prims) const;

public:

    //! Group all primitives by an integer value.
    bool Group(TMap<int32, TArray<GA_Primitive*> >& Prims) const;

    //! Group all primitives by a string value.
    bool Group(TMap<FString, TArray<GA_Primitive*> >& Prims) const;

    //! Group all primitives by an object value.
    bool Group(TMap<UObject*, TArray<GA_Primitive*> >& Prims) const;

public:

    //! Group given primitives by an integer value.
    bool Group(const TArray<GA_Primitive*>& Input, TMap<int32, TArray<GA_Primitive*> >& Prims) const;

    //! Group given primitives by a string value.
    bool Group(const TArray<GA_Primitive*>& Input, TMap<FString, TArray<GA_Primitive*> >& Prims) const;

    //! Group given primitives by an object value.
    bool Group(const TArray<GA_Primitive*>& Input, TMap<UObject*, TArray<GA_Primitive*> >& Prims) const;

public:

    //! Given a list of primitives, get their integer attribute values.
    bool Get(const TArray<GA_Primitive*>& Prims, TArray<int32>& Values) const;

    //! Given a list of primitives, get their string attribute values.
    bool Get(const TArray<GA_Primitive*>& Prims, TArray<FString>& Values) const;

    //! Given a list of primitives, get their object attribute values.
    bool Get(const TArray<GA_Primitive*>& Prims, TArray<UObject*>& Values) const;

public:

    //! Get integer attribute values for all primitives.
    bool GetAll(TArray<int32>& Values) const;

    //! Get string attribute values for all primitives.
    bool GetAll(TArray<FString>& Values) const;

    //! Get object attribute values for all primitives.
    bool GetAll(TArray<UObject*>& Values) const;
};

