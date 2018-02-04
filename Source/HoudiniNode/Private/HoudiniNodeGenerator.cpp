#include "HoudiniNodeGenerator.h"
#include "HoudiniNodeClass.h"
#include "HoudiniNodeActor.h"
#include "HoudiniNodePrivatePCH.h"


UHoudiniNodeGenerator::UHoudiniNodeGenerator(const FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer),
    GeneratorName(TEXT(""))
{

}


bool
UHoudiniNodeGenerator::Generate(UHoudiniNodeClass* NodeClass, TArray<AActor*>& GeneratedActors)
{
    GeneratedActors.Empty();

    if(!NodeClass)
    {
        return false;
    }

    if(!GetCurrentWorld(NodeClass))
    {
        return false;
    }

    TSharedPtr<FHoudiniNodeDetail> Detail = NodeClass->GetDetail();
    if(!Detail.IsValid())
    {
        return false;
    }

    return true;
}


UWorld*
UHoudiniNodeGenerator::GetCurrentWorld(UHoudiniNodeClass* NodeClass) const
{
    if(!NodeClass)
    {
        return nullptr;
    }

    AHoudiniNodeActor* HoudiniNodeActor = NodeClass->GetHoudiniNodeActor();
    if(!HoudiniNodeActor)
    {
        return nullptr;
    }

    return HoudiniNodeActor->GetWorld();
}


bool
UHoudiniNodeGenerator::DoesSupportClass(UClass* Class) const
{
    for(int32 Idx = 0; Idx < SupportedClasses.Num(); ++Idx)
    {
        UClass* SupportedClass = SupportedClasses[Idx];
        if(SupportedClass == Class)
        {
            return true;
        }
    }

    return false;
}


bool
UHoudiniNodeGenerator::DoesSupport(UObject* Object) const
{
    if(!Object)
    {
        return false;
    }

    return DoesSupportClass(Object->GetClass());
}


const TArray<UClass*>&
UHoudiniNodeGenerator::GetSupportedClasses() const
{
    return SupportedClasses;
}


const FString&
UHoudiniNodeGenerator::GetGeneratorName() const
{
    return GeneratorName;
}


bool
UHoudiniNodeGenerator::MatchName(const FString& InGeneratorName) const
{
    if(InGeneratorName.Equals(GeneratorName, ESearchCase::IgnoreCase))
    {
        return true;
    }

    return false;
}


void
UHoudiniNodeGenerator::Prepare()
{

}


void
UHoudiniNodeGenerator::CleanUp()
{

}


bool
UHoudiniNodeGenerator::Discard(UObject* Object) const
{
    if(!Object)
    {
        return false;
    }

    FString ObjectName = Object->GetName();
    const FString& GeneratorClass = GetClass()->GetName();

    AActor* Actor = Cast<AActor>(Object);
    if(Actor)
    {
        UWorld* World = Actor->GetWorld();
        if(World)
        {
            World->EditorDestroyActor(Actor, true);
        }
        else
        {
            Actor->ConditionalBeginDestroy();
        }
    }
    else
    {
        Object->ConditionalBeginDestroy();
    }

    return true;
}


bool
UHoudiniNodeGenerator::Discard(const TArray<UObject*>& Objects) const
{
    bool Result = false;

    for(int32 Idx = 0; Idx < Objects.Num(); ++Idx)
    {
        UObject* Object = Objects[Idx];
        Result |= Discard(Object);
    }

    return Result;
}

