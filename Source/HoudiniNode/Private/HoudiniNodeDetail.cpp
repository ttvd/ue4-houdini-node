#include "HoudiniNodePrivatePCH.h"
#include "HoudiniNodeDetail.h"

#pragma warning(push)
#pragma warning(disable : 4706)


FHoudiniNodeDetail::FHoudiniNodeDetail(OBJ_Node* InNode) :
    Node(InNode)
{

}


bool
FHoudiniNodeDetail::Cook(float Time)
{
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

    GU_DetailHandle DetailHandle = DisplaySop->getCookedGeoHandle(Context, ForcedCook);
    if(!DetailHandle.isValid())
    {
        return false;
    }

    GU_DetailHandleAutoReadLock DetailLock(DetailHandle);
    Detail = const_cast<GU_Detail*>(DetailLock.getGdp());
    if(!Detail)
    {
        return false;
    }

    return true;
}


bool
FHoudiniNodeDetail::IsValid() const
{
    return Detail != nullptr;
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


#pragma warning(pop)

