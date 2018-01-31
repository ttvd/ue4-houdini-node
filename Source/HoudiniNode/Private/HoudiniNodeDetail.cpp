#include "HoudiniNodeDetail.h"
#include "HoudiniNodePrivatePCH.h"
#include "HoudiniNodeAttributePrimitive.h"


#pragma warning(push)
#pragma warning(disable : 4706)


FHoudiniNodeDetail::FHoudiniNodeDetail(OBJ_Node* InNode) :
    Node(InNode)
{

}


FHoudiniNodeDetail::~FHoudiniNodeDetail()
{
    Reset();
}


void
FHoudiniNodeDetail::Reset()
{
    if(DetailHandle.isValid() && DetailHandle.hasActiveLock())
    {
        DetailHandle.unlock(Detail);
    }

    DetailHandle.clear();
    Detail = nullptr;
    Time = 0.0f;
}


bool
FHoudiniNodeDetail::Cook(float InTime)
{
    Reset();
    Time = InTime;

    if(!Node)
    {
        return false;
    }

    SOP_Node* DisplaySop = Node->getDisplaySopPtr();
    if(!DisplaySop)
    {
        return false;
    }

    OP_Context Context(Time);
    const int32 ForcedCook = 1;

    DetailHandle = DisplaySop->getCookedGeoHandle(Context, ForcedCook);
    if(!DetailHandle.isValid())
    {
        Reset();
        return false;
    }

    Detail = const_cast<GU_Detail*>(DetailHandle.readLock());
    if(!Detail)
    {
        Reset();
        return false;
    }

    return true;
}


float
FHoudiniNodeDetail::GetCookTime() const
{
    return Time;
}


bool
FHoudiniNodeDetail::IsValid() const
{
    if(DetailHandle.isValid() && DetailHandle.hasActiveLock())
    {
        if(Detail && Node)
        {
            return true;
        }
    }

    return false;
}


bool
FHoudiniNodeDetail::GetAllPrimitives(TArray<GA_Primitive*>& Primitives) const
{
    Primitives.Empty();

    if(!IsValid())
    {
        return false;
    }

    GA_Primitive* Prim = nullptr;

    GA_FOR_ALL_PRIMITIVES(Detail, Prim)
    {
        if(Prim)
        {
            Primitives.Add(Prim);
        }
    }

    return Primitives.Num() > 0;
}


bool
FHoudiniNodeDetail::GetAllPoints(TArray<GA_Offset>& Points) const
{
    Points.Empty();

    if(!IsValid())
    {
        return false;
    }

    GA_Offset PointOffset = GA_INVALID_OFFSET;

    GA_FOR_ALL_PTOFF(Detail, PointOffset)
    {
        if(GA_INVALID_OFFSET != PointOffset)
        {
            Points.Add(PointOffset);
        }
    }

    return Points.Num() > 0;
}


bool
FHoudiniNodeDetail::GetParts(TMap<int32, TArray<GA_Primitive*> >& Parts) const
{
    Parts.Empty();

    if(!IsValid())
    {
        return false;
    }

    FHoudiniNodeAttributePrimitive Attribute(Detail, HOUDINI_NODE_ATTRIBUTE_PART);
    if(!Attribute.IsValid())
    {
        return false;
    }

    if(!Attribute.Group(Parts))
    {
        return false;
    }

    return true;
}


#pragma warning(pop)

