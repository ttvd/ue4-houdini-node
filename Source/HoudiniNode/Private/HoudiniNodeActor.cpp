#include "HoudiniNodePrivatePCH.h"
#include "HoudiniNodeActor.h"
#include "HoudiniNodeAsset.h"
#include "HoudiniNodeComponent.h"
#include "HoudiniNodeClass.h"


AHoudiniNodeActor::AHoudiniNodeActor(const FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer),
    HoudiniNodeAsset(nullptr),
    HoudiniNodeComponent(nullptr)
{

}


AHoudiniNodeActor::~AHoudiniNodeActor()
{

}


/*
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
*/


#if WITH_EDITOR

void
AHoudiniNodeActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    if(HasAnyFlags(RF_Transient))
    {
        return;
    }

    UProperty* Property = PropertyChangedEvent.MemberProperty;
    if(!Property)
    {
        return;
    }

    if(Property->GetName() == TEXT("HoudiniNodeAsset"))
    {
        if(HoudiniNodeComponent)
        {
            UClass* HoudiniNodeComponentClass = HoudiniNodeComponent->GetClass();

            HoudiniNodeComponent->DestroyComponent();
            HoudiniNodeComponent = nullptr;

            HoudiniNodeComponentClass->ConditionalBeginDestroy();
        }

        if(HoudiniNodeAsset)
        {
            UClass* OriginalComponentClass = UHoudiniNodeComponent::StaticClass();

            const FGuid& Guid = FGuid::NewGuid();
            const FString& GuidString = Guid.ToString();
            const FString& ClassName = FString::Printf(TEXT("HoudiniNodeClass_%s"), *GuidString);

            UHoudiniNodeClass* HoudiniNodeClass = NewObject<UHoudiniNodeClass>(GetOutermost(), *ClassName, RF_Public | RF_Transactional);

            HoudiniNodeClass->HoudiniNodeAsset = HoudiniNodeAsset;

            HoudiniNodeClass->ClassGeneratedBy = this;
            HoudiniNodeClass->SetSuperStruct(OriginalComponentClass);
            HoudiniNodeClass->ClassConstructor = OriginalComponentClass->ClassConstructor;
            HoudiniNodeClass->PropertiesSize = OriginalComponentClass->PropertiesSize;

            HoudiniNodeClass->ClassAddReferencedObjects = UHoudiniNodeComponent::AddReferencedObjects;
            HoudiniNodeClass->AssembleReferenceTokenStream();

            UObject* CreatedComponent = StaticConstructObject_Internal(HoudiniNodeClass, this, NAME_None, RF_Public | RF_Transactional);
            HoudiniNodeComponent = Cast<UHoudiniNodeComponent>(CreatedComponent);
            if(HoudiniNodeComponent)
            {
                SetRootComponent(HoudiniNodeComponent);
                HoudiniNodeComponent->RegisterComponent();
            }
        }
    }
}

#endif

