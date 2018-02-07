#include "HoudiniNodeClass.h"
#include "HoudiniNodePrivatePCH.h"
#include "HoudiniNodeModule.h"
#include "HoudiniNodeAsset.h"
#include "HoudiniNodeGenerator.h"
#include "HoudiniNodeActor.h"
#include "HoudiniNodeComponent.h"
#include "HoudiniNodeAttributePrimitive.h"
#include "HoudiniNodePropertyFloat.h"
#include "HoudiniNodePropertyInt.h"
#include "HoudiniNodePropertyString.h"
#include "HoudiniNodePropertyEnum.h"


UHoudiniNodeClass::UHoudiniNodeClass(const FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer),
    HoudiniNodeAsset(nullptr),
    Node(nullptr),
    Library(nullptr),
    Component(nullptr),
    LibraryPath(TEXT("")),
    Time(0.0f),
    Scale(100.0f)
{

}


UHoudiniNodeClass::~UHoudiniNodeClass()
{
    DestroyNode();
    RemoveLibrary();
}


AHoudiniNodeActor*
UHoudiniNodeClass::GetHoudiniNodeActor() const
{
    if(Component)
    {
        return Cast<AHoudiniNodeActor>(Component->GetOwner());
    }

    return nullptr;
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


FHoudiniNodeDetail&
UHoudiniNodeClass::GetDetail() const
{
    return *(Detail.Get());
}


float
UHoudiniNodeClass::GetCookTime() const
{
    return Time;
}


void
UHoudiniNodeClass::SetCookTime(float InTime)
{
    Time = InTime;
}


void
UHoudiniNodeClass::SetScale(float InScale)
{
    Scale = InScale;
}


float
UHoudiniNodeClass::GetScale() const
{
    return Scale;
}


void
UHoudiniNodeClass::ResetDetail()
{
    if(Detail.IsValid())
    {
        Detail.Reset();
    }
}


bool
UHoudiniNodeClass::CookDetail()
{
    ResetDetail();

    if(!Node)
    {
        return false;
    }

    SOP_Node* DisplaySop = Node->getDisplaySopPtr();
    if(!DisplaySop)
    {
        ResetDetail();
        return false;
    }

    Detail = MakeShareable(new FHoudiniNodeDetail(DisplaySop, Scale));
    if(!Detail->Cook(Time))
    {
        ResetDetail();
        return false;
    }

    OnCookComplete();
    return true;
}


void
UHoudiniNodeClass::OnCookComplete()
{
    const TArray<UHoudiniNodeGenerator*>& Generators = GHoudiniNode->GetGenerators();

    TMap<FString, TArray<AActor*> > AllGeneratedActors;

    for(int32 Idx = 0; Idx < Generators.Num(); ++Idx)
    {
        UHoudiniNodeGenerator* Generator = Generators[Idx];
        if(!Generator)
        {
            continue;
        }

        Generator->Prepare();

        TArray<AActor*> GeneratedActors;
        if(Generator->Generate(this, GeneratedActors))
        {
            const FString& GeneratorName = Generator->GetGeneratorName();
            AllGeneratedActors.Add(GeneratorName, GeneratedActors);
        }

        Generator->CleanUp();
    }

    if(AllGeneratedActors.Num() > 0)
    {
        AHoudiniNodeActor* HoudiniNodeActor = GetHoudiniNodeActor();
        if(HoudiniNodeActor)
        {
            HoudiniNodeActor->RegisterGeneratedActors(AllGeneratedActors);
        }
    }
}


bool
UHoudiniNodeClass::OnParameterChanged(UProperty* Property)
{
    if(!Property)
    {
        return false;
    }

    const FString& PropertyName = Property->GetMetaData(TEXT("HoudiniName"));

    if(!CookDetail())
    {
        return false;
    }

    return true;
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

    TArray<IHoudiniNodePropertyInterface*> CreatedProperties;

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
            Offset = CreateParameter(Template, CreatedProperties);
        }

        Template += Offset;
    }

    {
        Children = nullptr;
        Algo::Reverse(CreatedProperties);

        for(int32 Idx = 0; Idx < CreatedProperties.Num(); ++Idx)
        {
            FHoudiniNodePropertyCommon* Property = dynamic_cast<FHoudiniNodePropertyCommon*>(CreatedProperties[Idx]);
            if(Property)
            {
                Property->AssignClass();
            }
        }
    }

    return true;
}


int32
UHoudiniNodeClass::CreateParameter(const PRM_Template* Template, TArray<IHoudiniNodePropertyInterface*>& CreatedProperties)
{
    if(!Template)
    {
        return 1;
    }

    const PRM_Type& Type = Template->getType();
    const PRM_Type::PRM_BasicType& BasicType = Type.getBasicType();

    const PRM_Name* TemplateName = Template->getNamePtr();
    if(!TemplateName)
    {
        return 1;
    }

    const UT_String& Label = TemplateName->getToken();
    FString PropertyName = UTF8_TO_TCHAR(Label.c_str());

    static const EObjectFlags PropertyObjectFlags = RF_Public | RF_Transient;

    int32 Offset = 1;
    IHoudiniNodePropertyInterface* Property = nullptr;

    {
        IHoudiniNodePropertyInterface** FoundProperty = Properties.Find(PropertyName);
        if(FoundProperty)
        {
            Property = *FoundProperty;
        }
    }

    if(Property)
    {
        Property->Update(Node, Time);
    }
    else
    {
        if(Type.isBasicType(PRM_Type::PRM_BASIC_FLOAT))
        {
            const PRM_Type::PRM_FloatType& TypeFloat = Type.getFloatType();

            if(TypeFloat == PRM_Type::PRM_FLOAT_INTEGER)
            {
                const PRM_ChoiceList* ChoiceList = Template->getChoiceListPtr();
                if(ChoiceList)
                {
                    Property = NewObject<UHoudiniNodePropertyEnum>(this, *PropertyName, PropertyObjectFlags);
                }
                else
                {
                    Property = NewObject<UHoudiniNodePropertyInt>(this, *PropertyName, PropertyObjectFlags);
                }
            }
            else if(TypeFloat == PRM_Type::PRM_FLOAT_RGBA)
            {
                // Make color.
                volatile int i = 5;
            }
            else
            {
                Property = NewObject<UHoudiniNodePropertyFloat>(this, *PropertyName, PropertyObjectFlags);
            }
        }
        else if(Type.isBasicType(PRM_Type::PRM_BASIC_ORDINAL))
        {
            const PRM_Type::PRM_OrdinalType& TypeOrdinal = Type.getOrdinalType();

            if(TypeOrdinal == PRM_Type::PRM_ORD_CALLBACK)
            {
                volatile int i = 5;
            }
            else if(TypeOrdinal == PRM_Type::PRM_ORD_TOGGLE)
            {
                // Radio.
                volatile int i = 5;
            }
            else if(TypeOrdinal == PRM_Type::PRM_ORD_SWITCHERLIST)
            {
                int i = 5;
            }
            else
            {
                const PRM_ChoiceList* ChoiceList = Template->getChoiceListPtr();
                if(ChoiceList)
                {
                    Property = NewObject<UHoudiniNodePropertyEnum>(this, *PropertyName, PropertyObjectFlags);
                }
                else
                {
                    Property = NewObject<UHoudiniNodePropertyInt>(this, *PropertyName, PropertyObjectFlags);
                }
            }
        }
        else if(Type.isBasicType(PRM_Type::PRM_BASIC_STRING))
        {
            // Paths, labels and separators.
            
            const PRM_Type::PRM_StringType& TypeString = Type.getStringType();

            if(TypeString == PRM_Type::PRM_STR_SEPARATOR)
            {
                volatile int i = 5;
            }
            else if(TypeString == PRM_Type::PRM_STR_LABEL)
            {
                volatile int i = 5;
            }
            else if(TypeString == PRM_Type::PRM_STR_PATH)
            {
                volatile int i = 5;
            }
            else if(TypeString == PRM_Type::PRM_STR_NONE)
            {
                Property = NewObject<UHoudiniNodePropertyString>(this, *PropertyName, PropertyObjectFlags);
            }
        }

        if(Property)
        {
            Property->Construct(Node, Template, Component, Time);

            CreatedProperties.Add(Property);
            Properties.Add(PropertyName, Property);
        }
    }

    return Offset;
}

