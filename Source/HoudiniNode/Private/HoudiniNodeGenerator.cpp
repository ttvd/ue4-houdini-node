#include "HoudiniNodeGenerator.h"
#include "HoudiniNodePrivatePCH.h"


UHoudiniNodeGenerator::UHoudiniNodeGenerator(const FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer)
{

}


bool
UHoudiniNodeGenerator::Generate(GU_Detail* Detail, TArray<AActor*>& GeneratedActors)
{
    GeneratedActors.Empty();

    if(!Detail)
    {
        return false;
    }

    return true;
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

