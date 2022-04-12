#pragma once
#include "HoudiniNodeDetail.h"

class GU_Detail;
class GA_Primitive;


class HOUDININODE_API FHoudiniNodeAttribute
{
public:

    //! Create attribute object for a given detail.
    FHoudiniNodeAttribute(const FHoudiniNodeDetail& InDetail, const FString& InName, GA_AttributeOwner InOwner);

public:

    //! Return true if this is a valid attribute.
    bool IsValid() const;

    //! Return true if this attribute exists.
    bool Exists() const;

public:

    //! Return tuple size, return 0 if attribute is invalid.
    int32 GetTupleSize() const;

public:

    //! Return the name of this attribute.
    const FString& GetName() const;

public:

    //! Locate an attribute handle for reading.
    template<typename TAttribType> TAttribType FindAttributeHandle(int32 TupleSize) const;

protected:

    //! Detail associated with this attribute.
    const FHoudiniNodeDetail& Detail;

    //! Owner of this attribute.
    GA_AttributeOwner Owner;

    //! Name of this attribute.
    FString Name;
    UT_String NameRaw;
};


template<typename TAttribType>
TAttribType
FHoudiniNodeAttribute::FindAttributeHandle(int32 TupleSize) const
{
    if(!Detail.IsValid())
    {
        return TAttribType();
    }

    GA_Attribute* Attribute = Detail.FindAttribute(NameRaw, Owner);
    if(!Attribute)
    {
        return TAttribType();
    }

    if(Attribute->getTupleSize() != TupleSize)
    {
        return TAttribType();
    }

    TAttribType AttributeHandle(Attribute);
    if(!AttributeHandle.isValid())
    {
        return TAttribType();
    }

    return AttributeHandle;
}

