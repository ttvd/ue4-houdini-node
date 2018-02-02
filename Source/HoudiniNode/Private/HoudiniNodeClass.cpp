#include "HoudiniNodeClass.h"
#include "HoudiniNodePrivatePCH.h"
#include "HoudiniNodeModule.h"
#include "HoudiniNodeAsset.h"
#include "HoudiniNodeComponent.h"
#include "HoudiniNodeAttributePrimitive.h"

#pragma warning(push)
#pragma warning(disable : 4706)


UHoudiniNodeClass::UHoudiniNodeClass(const FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer),
    HoudiniNodeAsset(nullptr),
    Node(nullptr),
    Library(nullptr),
    Detail(nullptr),
    Component(nullptr),
    LibraryPath(TEXT("")),
    Time(0.0f)
{

}


UHoudiniNodeClass::~UHoudiniNodeClass()
{
    DestroyNode();
    RemoveLibrary();
}


bool
UHoudiniNodeClass::AddLibrary()
{
    MOT_Director* Director = GHoudiniNode->GetDirector();
    if(!Director)
    {
        return false;
    }

    if(!HoudiniNodeAsset)
    {
        return false;
    }

    FString Filename(TEXT(""));
    if(!HoudiniNodeAsset->GetFilename(Filename))
    {
        return false;
    }

    OP_OTLManager& Manager = Director->getOTLManager();
    UT_WorkBuffer WorkBuffer;

    UT_String RawFilename = TCHAR_TO_UTF8(*Filename);

    Library = Manager.addLibrary(RawFilename.c_str(), OTL_INTERNAL_META, true, false, WorkBuffer);
    if(Library)
    {
        LibraryPath = Filename;
        return true;
    }

    return false;
}


bool
UHoudiniNodeClass::RemoveLibrary()
{
    MOT_Director* Director = GHoudiniNode->GetDirector();
    if(!Director)
    {
        return false;
    }

    if(!HoudiniNodeAsset)
    {
        return false;
    }

    if(!HasLibrary())
    {
        return false;
    }

    OP_OTLManager& Manager = Director->getOTLManager();

    UT_String RawFilename = TCHAR_TO_UTF8(*LibraryPath);
    Manager.removeLibrary(RawFilename.c_str(), "", false);

    Library = nullptr;
    LibraryPath = TEXT("");

    return true;
}


bool
UHoudiniNodeClass::HasLibrary() const
{
    if(Library && !LibraryPath.IsEmpty())
    {
        return true;
    }

    return false;
}


bool
UHoudiniNodeClass::GetAssetNames(TArray<UT_String>& AssetNames) const
{
    AssetNames.Empty();

    if(!HasLibrary())
    {
        return false;
    }

    const int32 DefitionsNum = Library->getNumDefinitions();
    for(int32 Idx = 0; Idx < DefitionsNum; ++Idx)
    {
        const OP_OTLDefinition& Definition = Library->getDefinition(Idx);
        const UT_String& RawAssetName = Definition.getName();
        AssetNames.Add(RawAssetName);
    }

    return AssetNames.Num() > 0;
}


bool
UHoudiniNodeClass::CreateNode()
{
    TArray<UT_String> AssetNames;
    if(GetAssetNames(AssetNames))
    {
        const UT_String& AssetName = AssetNames[0];
        return CreateNode(AssetName);
    }

    return false;
}


bool
UHoudiniNodeClass::CreateNode(const UT_String& NodeName)
{
    if(!NodeName.isstring())
    {
        return false;
    }

    if(Node)
    {
        return false;
    }

    OP_Network* ObjNetwork = GHoudiniNode->GetObjNetwork();
    if(!ObjNetwork)
    {
        return false;
    }

    Node = (OBJ_Node*) ObjNetwork->createNode(NodeName.c_str());
    if(!Node)
    {
        return false;
    }

    Node->runCreateScript();

    return true;
}


bool
UHoudiniNodeClass::DestroyNode()
{
    if(!Node)
    {
        return false;
    }

    OP_Network* ObjNetwork = GHoudiniNode->GetObjNetwork();
    if(!ObjNetwork)
    {
        return false;
    }

    ObjNetwork->destroyNode(Node);
    Node = nullptr;

    return true;
}


OBJ_Node*
UHoudiniNodeClass::GetNode() const
{
    return Node;
}


float
UHoudiniNodeClass::GetCookTime() const
{
    return Time;
}


GU_Detail*
UHoudiniNodeClass::GetDetail() const
{
    return Detail;
}


bool
UHoudiniNodeClass::GetAllPrimitives(TArray<GA_Primitive*>& Primitives) const
{
    Primitives.Empty();

    if(!Detail)
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
UHoudiniNodeClass::GetAllPoints(TArray<GA_Offset>& Points) const
{
    Points.Empty();

    if(!Detail)
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
UHoudiniNodeClass::GetParts(TMap<int32, TArray<GA_Primitive*> >& Parts) const
{
    Parts.Empty();

    if(!Detail)
    {
        return false;
    }

    const int32 NumPrims = Detail->getNumPrimitives();
    if(!NumPrims)
    {
        return false;
    }

    FHoudiniNodeAttributePrimitive Attribute(Detail, HOUDINI_NODE_ATTRIBUTE_PART);
    if(Attribute.IsValid())
    {
        if(Attribute.Group(Parts))
        {
            return true;
        }
    }

    TArray<GA_Primitive*> AllPrimitives;
    if(GetAllPrimitives(AllPrimitives))
    {
        Parts.Add(0, AllPrimitives);
    }

    return false;
}


bool
UHoudiniNodeClass::GetGroupPrimitives(const FString& GroupName, TArray<GA_Primitive*>& Primitives) const
{
    Primitives.Empty();

    if(!Detail)
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
UHoudiniNodeClass::GetGroupPrimitives(const FString& GroupName, TMap<int32, TArray<GA_Primitive*> >& Parts) const
{
    if(!Detail)
    {
        return false;
    }

    TArray<GA_Primitive*> Primitives;
    if(!GetGroupPrimitives(GroupName, Primitives))
    {
        return false;
    }

    FHoudiniNodeAttributePrimitive Attribute(Detail, HOUDINI_NODE_ATTRIBUTE_PART);
    if(Attribute.IsValid())
    {
        if(Attribute.Group(Primitives, Parts))
        {
            return true;
        }
    }

    Parts.Add(0, Primitives);
    return true;
}


void
UHoudiniNodeClass::ResetDetail()
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
UHoudiniNodeClass::CookDetail(float InTime)
{
    ResetDetail();

    if(!Node)
    {
        return false;
    }

    Time = InTime;

    SOP_Node* DisplaySop = Node->getDisplaySopPtr();
    if(!DisplaySop)
    {
        ResetDetail();
        return false;
    }

    OP_Context Context(Time);
    const int32 ForcedCook = 1;

    DetailHandle = DisplaySop->getCookedGeoHandle(Context, ForcedCook);
    if(!DetailHandle.isValid())
    {
        ResetDetail();
        return false;
    }

    Detail = const_cast<GU_Detail*>(DetailHandle.readLock());
    if(!Detail)
    {
        ResetDetail();
        return false;
    }

    return true;
}


bool
UHoudiniNodeClass::OnParameterChanged(UProperty* Property)
{
    if(!Property)
    {
        return false;
    }

    const FString& PropertyName = Property->GetMetaData(TEXT("HoudiniName"));

    if(!CookDetail(0.0f))
    {
        return false;
    }



    return true;
}


void
UHoudiniNodeClass::AssignPropertyOffset(UProperty* Property, uint32 Offset) const
{
    if(!Property)
    {
        return;
    }

    *(int32*)((char*) &Property->RepNotifyFunc - sizeof(int32)) = (int32) Offset;
}


bool
UHoudiniNodeClass::CreateParameters(UHoudiniNodeComponent* HoudiniNodeComponent)
{
    if(!Node)
    {
        return false;
    }

    Component = HoudiniNodeComponent;
    if(!Component)
    {
        return false;
    }

    OP_Operator* Op = Node->getOperator();
    if(!Op)
    {
        return false;
    }

    const PRM_Template* Template = nullptr;

    Template = Node->getSpareParmLayoutTemplates();
    if(!Template)
    {
        Template = Op->getLayoutParmTemplates();
    }

    if(!Template)
    {
        Template = Op->getParmTemplates();
    }

    if(!Template)
    {
        return false;
    }

    while(Template && Template->getType() != PRM_LIST_TERMINATOR)
    {
        const PRM_Type& Type = Template->getType();
        int32 Offset = 1;

        if(Type.isVisible())
        {
            Offset = CreateParameter(Template);
        }

        Template += Offset;
    }

    return true;
}


int32
UHoudiniNodeClass::CreateParameter(const PRM_Template* Template)
{
    if(!Template)
    {
        return 1;
    }

    const PRM_Type& Type = Template->getType();
    const PRM_Type::PRM_BasicType& BasicType = Type.getBasicType();

    int32 Offset = 1;

    if(Type.isBasicType(PRM_Type::PRM_BASIC_FLOAT))
    {
        const PRM_Type::PRM_FloatType& TypeFloat = Type.getFloatType();

        if(TypeFloat == PRM_Type::PRM_FLOAT_INTEGER)
        {
            // Make integer.
            volatile int i = 5;
        }
        else if(TypeFloat == PRM_Type::PRM_FLOAT_RGBA)
        {
            // Make color.
            volatile int i = 5;
        }
        else
        {
            Offset = CreateParameterFloat(Template);
        }
    }
    else if(Type.isBasicType(PRM_Type::PRM_BASIC_ORDINAL))
    {
        const PRM_Type::PRM_OrdinalType& TypeOrdinal = Type.getOrdinalType();

        if(TypeOrdinal == PRM_Type::PRM_ORD_CALLBACK)
        {
            // Menu.
            volatile int i = 5;
        }
        else if(TypeOrdinal == PRM_Type::PRM_ORD_TOGGLE)
        {
            // Radio.
            volatile int i = 5;
        }
        else
        {
            // Integer.
            volatile int i = 5;
        }
    }
    else if(Type.isBasicType(PRM_Type::PRM_BASIC_STRING))
    {
        // Paths, labels and separators.
        volatile int i = 5;
    }

    return Offset;
}


int32
UHoudiniNodeClass::CreateParameterFloat(const PRM_Template* Template)
{
    const PRM_Name* TemplateName = Template->getNamePtr();
    const UT_String& Name = TemplateName->getToken();

    const int32 VectorSize = Template->getVectorSize();
    if(!VectorSize)
    {
        return 1;
    }

    TArray<float> Values;
    Values.SetNumZeroed(VectorSize);

    for(int32 Idx = 0; Idx < VectorSize; ++Idx)
    {
        const float Value = Node->evalFloat(Name.c_str(), Idx, Time);
        Values[Idx] = Value;
    }

    UProperty* Property = CreateParameterCommon<UFloatProperty>(Template, Values);
    return 1;
}

#pragma warning(pop)

