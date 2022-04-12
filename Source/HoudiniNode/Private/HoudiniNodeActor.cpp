#include "HoudiniNodeActor.h"
#include "HoudiniNodePrivatePCH.h"
#include "HoudiniNodeAsset.h"
#include "HoudiniNodeComponent.h"
#include "HoudiniNodeClass.h"
#include "HoudiniNodeGenerator.h"
#include "HoudiniNodeModule.h"


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
AHoudiniNodeActor::AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector)
{
    AHoudiniNodeActor* HoudiniNodeActor = Cast<AHoudiniNodeActor>(InThis);
    if(!HoudiniNodeActor)
    {
        return;
    }

    for(TMap<UHoudiniNodeGenerator*, TArray<AActor*> >::TIterator Iter(HoudiniNodeActor->GeneratedActors); Iter; ++Iter)
    {
        UHoudiniNodeGenerator* ActorGenerator = Iter.Key();
        const TArray<AActor*>& Actors = Iter.Value();

        if(ActorGenerator)
        {
            Collector.AddReferencedObject(ActorGenerator, InThis);
        }

        for(int32 Idx = 0; Idx < Actors.Num(); ++Idx)
        {
            AActor* Actor = Actors[Idx];
            if(Actor)
            {
                Collector.AddReferencedObject(Actor, InThis);
            }
        }
    }
}


void
AHoudiniNodeActor::RegisterGeneratedActors(const TMap<UHoudiniNodeGenerator*, TArray<AActor*> >& InGeneratedActors)
{
    // Discard current objects.
    {
        for(TMap<UHoudiniNodeGenerator*, TArray<AActor*> >::TIterator Iter(GeneratedActors); Iter; ++Iter)
        {
            UHoudiniNodeGenerator* ActorGenerator = Iter.Key();
            const TArray<AActor*>& Actors = Iter.Value();

            if(ActorGenerator)
            {
                ActorGenerator->Discard(Actors);
            }
        }

        GeneratedActors.Empty();
    }

    GeneratedActors = InGeneratedActors;

    // Attach new objects.
    {
        const FAttachmentTransformRules& AttachmentRules = FAttachmentTransformRules::KeepRelativeTransform;

        for(TMap<UHoudiniNodeGenerator*, TArray<AActor*> >::TIterator Iter(GeneratedActors); Iter; ++Iter)
        {
            UHoudiniNodeGenerator* ActorGenerator = Iter.Key();
            const TArray<AActor*>& Actors = Iter.Value();

            for(int32 Idx = 0; Idx < Actors.Num(); ++Idx)
            {
                AActor* Actor = Actors[Idx];
                Actor->AttachToActor(this, AttachmentRules);
            }
        }
    }
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
                HoudiniNodeComponent->SetMobility(EComponentMobility::Static);
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


