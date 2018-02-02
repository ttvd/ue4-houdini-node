#include "HoudiniNodeActor.h"
#include "HoudiniNodePrivatePCH.h"
#include "HoudiniNodeAsset.h"
#include "HoudiniNodeComponent.h"
#include "HoudiniNodeClass.h"


AHoudiniNodeActor::AHoudiniNodeActor(const FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer),
    Asset(nullptr),
    Time(0.0f),
    Scale(100.0f),
    HoudiniNodeComponent(nullptr)
{

}


AHoudiniNodeActor::~AHoudiniNodeActor()
{

}


void
AHoudiniNodeActor::RegisterGeneratedActors(const TMap<FString, TArray<AActor*> >& GeneratedActors)
{

}


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

    if(Property->GetName() == TEXT("Asset"))
    {
        if(HoudiniNodeComponent)
        {
            UHoudiniNodeClass* HoudiniNodeComponentClass = Cast<UHoudiniNodeClass>(HoudiniNodeComponent->GetClass());

            HoudiniNodeComponent->DestroyComponent();
            HoudiniNodeComponent = nullptr;

            if(HoudiniNodeComponentClass)
            {
                HoudiniNodeComponentClass->RemoveLibrary();
                HoudiniNodeComponentClass->ConditionalBeginDestroy();
            }
        }

        if(Asset)
        {
            UClass* OriginalComponentClass = UHoudiniNodeComponent::StaticClass();

            const FGuid& Guid = FGuid::NewGuid();
            const FString& GuidString = Guid.ToString();
            const FString& ClassName = FString::Printf(TEXT("HoudiniNodeClass_%s"), *GuidString);

            UHoudiniNodeClass* HoudiniNodeClass = NewObject<UHoudiniNodeClass>(GetOutermost(), *ClassName, RF_Public | RF_Transactional);

            HoudiniNodeClass->HoudiniNodeAsset = Asset;

            HoudiniNodeClass->ClassGeneratedBy = this;
            HoudiniNodeClass->SetSuperStruct(OriginalComponentClass);
            HoudiniNodeClass->ClassConstructor = OriginalComponentClass->ClassConstructor;
            HoudiniNodeClass->PropertiesSize = OriginalComponentClass->PropertiesSize;
            HoudiniNodeClass->ClassDefaultObject = OriginalComponentClass->ClassDefaultObject;
            HoudiniNodeClass->ClassCastFlags = OriginalComponentClass->ClassCastFlags | CASTCLASS_USceneComponent;

            HoudiniNodeClass->ClassAddReferencedObjects = OriginalComponentClass->ClassAddReferencedObjects;
            HoudiniNodeClass->AssembleReferenceTokenStream();

            HoudiniNodeClass->ClassFlags = OriginalComponentClass->ClassFlags;

            HoudiniNodeComponent = NewObject<UHoudiniNodeComponent>(this, HoudiniNodeClass, NAME_None, RF_Public | RF_Transactional);
            if(HoudiniNodeComponent)
            {
                SetRootComponent(HoudiniNodeComponent);
                HoudiniNodeComponent->RegisterComponent();
            }

            HoudiniNodeClass->SetCookTime(Time);
            HoudiniNodeClass->SetScale(Scale);

            HoudiniNodeClass->AddLibrary();
            HoudiniNodeClass->CreateNode();

            HoudiniNodeClass->CreateParameters(HoudiniNodeComponent);
            HoudiniNodeClass->CookDetail();
        }
    }
    else if(Property->GetName() == TEXT("Scale"))
    {

    }
    else if(Property->GetName() == TEXT("Time"))
    {
        if(Time < FLT_MIN)
        {
            Time = 100.0f;
        }
    }
}

#endif


