#include "HoudiniNodePrivatePCH.h"
#include "HoudiniNodeActor.h"
#include "HoudiniNodeAsset.h"
#include "HoudiniNodeComponent.h"
#include "HoudiniNodeClass.h"


AHoudiniNodeActor::AHoudiniNodeActor(const FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer),
    HoudiniNodeAsset(nullptr),
    HoudiniNodeComponent(nullptr),
    Node(nullptr)
{

}


AHoudiniNodeActor::~AHoudiniNodeActor()
{

}


void
AHoudiniNodeActor::PostActorCreated()
{
    FString ClassName(TEXT("HoudiniNodeComponentPatched"));
    UClass* ComponentClass = UHoudiniNodeComponent::StaticClass();

    //UDynamicClass* Class = NewObject<UDynamicClass>(GetOutermost(), *ClassName, RF_Public | RF_Transactional);
    UHoudiniNodeClass* Class = NewObject<UHoudiniNodeClass>(GetOutermost(), *ClassName, RF_Public | RF_Transactional);
    if(!Class)
    {
        return;
    }

    Class->ClassGeneratedBy = this;
    Class->SetSuperStruct(ComponentClass);
    Class->ClassConstructor = ComponentClass->ClassConstructor;
    Class->PropertiesSize = ComponentClass->PropertiesSize;

    //Class->ClassDefaultObject = StaticAllocateObject(InClass, InOuter, InName, InFlags, EInternalObjectFlags::None, false);

    Class->ClassAddReferencedObjects = UHoudiniNodeComponent::AddReferencedObjects;
    Class->AssembleReferenceTokenStream();

    //ChildClass->Bind();
    //Class->StaticLink(true);

    UObject* CreatedComponent = StaticConstructObject_Internal(Class, this, NAME_None, RF_Public | RF_Transactional);
    HoudiniNodeComponent = Cast<UHoudiniNodeComponent>(CreatedComponent);
    if(HoudiniNodeComponent)
    {
        SetRootComponent(HoudiniNodeComponent);
        HoudiniNodeComponent->RegisterComponent();
    }

    UIntProperty* Property = nullptr;

    {
        static const EObjectFlags PropertyObjectFlags = RF_Public | RF_Transient;
        FString PropertyName(TEXT("HoudiniNodePropertyRuntime"));
        Property = NewObject<UIntProperty>(Class, *PropertyName, PropertyObjectFlags);
        //Class->ReferencedConvertedFields.Add(Property);

        Property->ArrayDim = 1;
        Property->PropertyFlags = UINT64_C(69793219077);

        Property->SetMetaData(TEXT("EditAnywhere"), TEXT("1"));
        Property->SetMetaData(TEXT("BlueprintReadOnly"), TEXT("1"));
        Property->SetMetaData(TEXT("Category"), TEXT("HoudiniProperties"));

        Class->AddCppProperty(Property);
    }

    {
        
        uint32* Ptr = (uint32*) HoudiniNodeComponent->GetCurrentScratchSpacePosition();
        *Ptr = 42u;

        const uint32 Offset = HoudiniNodeComponent->GetCurrentScratchSpaceOffset();
        *(int32*)((char*) &Property->RepNotifyFunc + sizeof(FName)) = Offset;

        HoudiniNodeComponent->IncrementScratchSpaceBufferOffset<uint32>();
    }
}


#if WITH_EDITOR

void
AHoudiniNodeActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    UProperty* Property = PropertyChangedEvent.MemberProperty;
    if(!Property)
    {
        return;
    }

    if(Property->GetName() == TEXT("HoudiniNodeAsset"))
    {

    }
}

#endif

