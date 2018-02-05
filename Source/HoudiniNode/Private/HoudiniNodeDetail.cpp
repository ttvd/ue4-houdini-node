#include "HoudiniNodeDetail.h"
#include "HoudiniNodePrivatePCH.h"


#pragma warning(push)
#pragma warning(disable : 4706)


FHoudiniNodeDetail::FHoudiniNodeDetail(SOP_Node* InNode, float InScale) :
    Node(InNode),
    Detail(nullptr),
    Time(0.0f),
    Scale(InScale)
{

}


FHoudiniNodeDetail::~FHoudiniNodeDetail()
{
    if(DetailHandle.isValid() && DetailHandle.hasActiveLock())
    {
        DetailHandle.unlock(Detail);
    }

    DetailHandle.clear();
}


GU_Detail*
FHoudiniNodeDetail::GetDetail() const
{
    return Detail;
}


float
FHoudiniNodeDetail::GetScale() const
{
    return Scale;
}


bool
FHoudiniNodeDetail::IsValid() const
{
    if(Detail)
    {
        return true;
    }

    return false;
}


bool
FHoudiniNodeDetail::Cook(float InTime)
{
    Time = InTime;

    OP_Context Context(Time);
    const int32 ForcedCook = 1;

    DetailHandle = Node->getCookedGeoHandle(Context, ForcedCook);
    if(!DetailHandle.isValid())
    {
        return false;
    }

    Detail = const_cast<GU_Detail*>(DetailHandle.readLock());
    if(!Detail)
    {
        DetailHandle.clear();
        return false;
    }

    return true;
}


GA_Attribute*
FHoudiniNodeDetail::FindAttribute(const FString& AttributeName, GA_AttributeOwner Owner) const
{
    if(!Detail)
    {
        return nullptr;
    }

    std::string RawString = TCHAR_TO_UTF8(*AttributeName);
    UT_String RawValue(RawString);

    return FindAttribute(RawValue, Owner);
}


GA_Attribute*
FHoudiniNodeDetail::FindAttribute(const UT_String& AttributeName, GA_AttributeOwner Owner) const
{
    if(!Detail)
    {
        return nullptr;
    }

    GA_Attribute* Attribute = Detail->findAttribute(Owner, AttributeName);
    return Attribute;
}



int32
FHoudiniNodeDetail::GetPrimitiveCount() const
{
    if(IsValid())
    {
        const int32 PrimitiveCount = Detail->getNumPrimitives();
        return PrimitiveCount;
    }

    return 0;
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
FHoudiniNodeDetail::GetAllPoints(TArray<uint32>& Points) const
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
FHoudiniNodeDetail::GetAllPointPositions(TArray<FVector>& Positions) const
{
    Positions.Empty();

    if(!IsValid())
    {
        return false;
    }

    GA_Offset PointOffset = GA_INVALID_OFFSET;

    GA_FOR_ALL_PTOFF(Detail, PointOffset)
    {
        if(PointOffset == GA_INVALID_OFFSET)
        {
            continue;
        }

        const UT_Vector3& Position = Detail->getPos3(PointOffset);
        FVector PointPosition(Position.x(), Position.z(), Position.y());
        PointPosition *= Scale;

        Positions.Add(PointPosition);
    }

    return Positions.Num() > 0;
}


bool
FHoudiniNodeDetail::GetPointPositions(const TArray<GA_Offset>& Points, TArray<FVector>& Positions) const
{
    Positions.Empty();

    if(!IsValid())
    {
        return false;
    }

    for(int32 Idx = 0; Idx < Points.Num(); ++Idx)
    {
        GA_Offset PointOffset = Points[Idx];

        if(PointOffset == GA_INVALID_OFFSET)
        {
            continue;
        }

        const UT_Vector3& Position = Detail->getPos3(PointOffset);
        FVector PointPosition(Position.x(), Position.z(), Position.y());
        PointPosition *= Scale;

        Positions.Add(PointPosition);
    }

    return Positions.Num() > 0;
}


bool
FHoudiniNodeDetail::GetPrimitivePointPositions(const TArray<GA_Primitive*>& Primitives, TArray<FVector>& Positions) const
{
    Positions.Empty();

    if(!IsValid())
    {
        return false;
    }

    TArray<GA_Offset> Points;
    if(!GetPrimitivePoints(Primitives, Points))
    {
        return false;
    }

    return GetPointPositions(Points, Positions);
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
FHoudiniNodeDetail::GetGroupPrimitives(const FString& GroupName, TArray<GA_Primitive*>& Primitives) const
{
    Primitives.Empty();

    if(!IsValid())
    {
        return false;
    }

    if(GroupName.IsEmpty())
    {
        return false;
    }

    std::string RawString = TCHAR_TO_UTF8(*GroupName);
    UT_String RawValue(RawString);

    GA_PrimitiveGroup* Group = Detail->findPrimitiveGroup(RawValue);
    if(!Group)
    {
        return false;
    }

    GA_Primitive* Prim = nullptr;

    GA_FOR_ALL_GROUP_PRIMITIVES(Detail, Group, Prim)
    {
        if(Prim)
        {
            Primitives.Add(Prim);
        }
    }

    return Primitives.Num() > 0;
}


bool
FHoudiniNodeDetail::GetPartPrims(TMap<FString, TMap<int32, TArray<GA_Primitive*> > >& Parts) const
{
    Parts.Empty();

    if(!IsValid())
    {
        return false;
    }

    const int32 NumPrims = Detail->getNumPrimitives();
    if(!NumPrims)
    {
        return false;
    }

    FHoudiniNodeAttributePrimitive AttributeGenerator(*this, HOUDINI_NODE_ATTRIBUTE_GENERATOR_PRIM);
    FHoudiniNodeAttributePrimitive AttributePart(*this, HOUDINI_NODE_ATTRIBUTE_PART);

    TMap<FString, TArray<GA_Primitive*> > AllGeneratorPrimitives;

    if(AttributeGenerator.IsValid() && AttributeGenerator.Group(AllGeneratorPrimitives))
    {
        for(TMap<FString, TArray<GA_Primitive*> >::TIterator Iter(AllGeneratorPrimitives); Iter; ++Iter)
        {
            const FString& GeneratorName = Iter.Key();
            TArray<GA_Primitive*>& GeneratorPrims = Iter.Value();

            if(AttributePart.IsValid())
            {
                TMap<int32, TArray<GA_Primitive*> > GeneratorParts;

                if(AttributePart.Group(GeneratorPrims, GeneratorParts))
                {
                    Parts.Add(GeneratorName, GeneratorParts);
                    continue;
                }
            }

            TMap<int32, TArray<GA_Primitive*> > SingleGeneratorPart;
            SingleGeneratorPart.Add(0, GeneratorPrims);
            Parts.Add(GeneratorName, SingleGeneratorPart);
        }
    }
    else
    {
        TArray<GA_Primitive*> AllPrimitives;
        if(GetAllPrimitives(AllPrimitives))
        {
            TMap<int32, TArray<GA_Primitive*> > GeneratorParts;

            if(AttributePart.IsValid() && AttributePart.Group(AllPrimitives, GeneratorParts))
            {
                Parts.Add(TEXT(""), GeneratorParts);
            }
            else
            {
                TMap<int32, TArray<GA_Primitive*> > SingleGeneratorPart;
                SingleGeneratorPart.Add(0, AllPrimitives);
                Parts.Add(TEXT(""), SingleGeneratorPart);
            }
        }
    }

    return Parts.Num() > 0;
}


bool
FHoudiniNodeDetail::GetPartPoints(TMap<FString, TMap<int32, TArray<GA_Offset> > >& Parts) const
{
    Parts.Empty();

    if(!IsValid())
    {
        return false;
    }

    return false;
}


bool
FHoudiniNodeDetail::GetPrimitivePoints(const TArray<GA_Primitive*>& Primitives, TArray<GA_Offset>& Points) const
{
    Points.Empty();

    if(!IsValid())
    {
        return false;
    }

    for(int32 Idx = 0; Idx < Primitives.Num(); ++Idx)
    {
        GA_Primitive* Prim = Primitives[Idx];
        if(!Prim)
        {
            continue;
        }

        GA_Offset PointOffset0 = Prim->getPointOffset(0);
        GA_Offset PointOffset1 = Prim->getPointOffset(1);
        GA_Offset PointOffset2 = Prim->getPointOffset(2);

        Swap(PointOffset1, PointOffset2);

        Points.Add(PointOffset0);
        Points.Add(PointOffset1);
        Points.Add(PointOffset2);
    }

    return Points.Num() > 0;
}


bool
FHoudiniNodeDetail::GetPrimitivePoints(const TArray<GA_Primitive*>& Primitives, TArray<uint32>& Points) const
{
    Points.Empty();

    if(!IsValid())
    {
        return false;
    }

    for(int32 Idx = 0; Idx < Primitives.Num(); ++Idx)
    {
        GA_Primitive* Prim = Primitives[Idx];
        if(!Prim)
        {
            continue;
        }

        GA_Offset PointOffset0 = Prim->getPointOffset(0);
        GA_Offset PointOffset1 = Prim->getPointOffset(1);
        GA_Offset PointOffset2 = Prim->getPointOffset(2);

        Swap(PointOffset1, PointOffset2);

        Points.Add(PointOffset0);
        Points.Add(PointOffset1);
        Points.Add(PointOffset2);
    }

    return Points.Num() > 0;
}

#pragma warning(pop)

