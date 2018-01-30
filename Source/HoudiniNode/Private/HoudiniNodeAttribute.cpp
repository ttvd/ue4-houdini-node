#include "HoudiniNodeAttribute.h"
#include "HoudiniNodePrivatePCH.h"


FHoudiniNodeAttribute::FHoudiniNodeAttribute(GU_Detail* InDetail, const FString& InName, GA_AttributeOwner InOwner) :
    Detail(InDetail),
    Owner(InOwner),
    Name(InName),
    NameRaw("")
{
    std::string RawString = TCHAR_TO_UTF8(*InName);
    NameRaw = UT_String(RawString);
}


const FString&
FHoudiniNodeAttribute::GetName() const
{
    return Name;
}


GU_Detail*
FHoudiniNodeAttribute::GetDetail() const
{
    return Detail;
}


bool
FHoudiniNodeAttribute::Exists() const
{
    GA_Attribute* Attribute = Detail->findAttribute(Owner, NameRaw);
    if(!Attribute)
    {
        return false;
    }

    return true;
}


int32
FHoudiniNodeAttribute::GetTupleSize() const
{
    GA_Attribute* Attribute = Detail->findAttribute(Owner, NameRaw);
    if(!Attribute)
    {
        return -1;
    }

    return Attribute->getTupleSize();
}


bool
FHoudiniNodeAttribute::IsValid() const
{
    if(!Detail)
    {
        return false;
    }

    if(!NameRaw.isValidVariableName())
    {
        return false;
    }

    switch(Owner)
    {
        case GA_ATTRIB_VERTEX:
        case GA_ATTRIB_POINT:
        case GA_ATTRIB_PRIMITIVE:
        case GA_ATTRIB_GLOBAL:
        {
            break;
        }

        default:
        {
            return false;
        }
    }

    if(!Exists())
    {
        return false;
    }

    return true;
}
