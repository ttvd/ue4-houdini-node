#include "HoudiniNodeModule.h"
#include "HoudiniNodePrivatePCH.h"
#include "HoudiniNodeGenerator.h"
#include "HoudiniNodeObjectPacker.h"


FHoudiniNode*
GHoudiniNode = nullptr;


FHoudiniNode::FHoudiniNode() :
    Director(nullptr),
    DefaultMaterial(nullptr)
{

}


FHoudiniNode::~FHoudiniNode()
{
    GHoudiniNode = nullptr;
}


void
FHoudiniNode::StartupModule()
{
    UT_UndoManager::disableUndoCreation();

    // Create and set director.
    {
        Director = new MOT_Director("HoudiniNode");
        ensure(Director);
        OPsetDirector(Director);

        PIcreateResourceManager();
    }

    GHoudiniNode = this;

    CreateGenerators();
    CreateObjectPackers();

    // Load default material.
    {
        DefaultMaterial = LoadObject<UMaterialInterface>(nullptr, HOUDINI_NODE_DEFAULT_MATERIAL, nullptr, LOAD_None, nullptr);
        ensure(DefaultMaterial);
    }
}


void
FHoudiniNode::ShutdownModule()
{
    if(Director)
    {
        /*
        Director->resetForNewFile();
        Director->runPostNewScript();
        */
        Director = nullptr;
    }
}


UMaterialInterface*
FHoudiniNode::GetDefaultMaterial() const
{
    return DefaultMaterial;
}


OP_Network*
FHoudiniNode::GetObjNetwork() const
{
    if(Director)
    {
        OP_Node* Node = Director->getChild("obj");
        if(Node && Node->isNetwork())
        {
            return (OP_Network*) Node;
        }
    }

    return nullptr;
}


MOT_Director*
FHoudiniNode::GetDirector() const
{
    return Director;
}


void
FHoudiniNode::AddReferencedObjects(FReferenceCollector& Collector)
{
    for(int32 Idx = 0; Idx < Generators.Num(); ++Idx)
    {
        UHoudiniNodeGenerator* Generator = Generators[Idx];
        Collector.AddReferencedObject(Generator);
    }

    for(TMap<UClass*, UHoudiniNodeObjectPacker*>::TIterator Iter(ObjectPackers); Iter; ++Iter)
    {
        UClass* Class = Iter.Key();
        UHoudiniNodeObjectPacker* ObjectPacker = Iter.Value();

        Collector.AddReferencedObject(ObjectPacker);
    }

    Collector.AddReferencedObject(DefaultMaterial);
}


bool
FHoudiniNode::CreateGenerators()
{
    Generators.Empty();

    for(TObjectIterator<UClass> It; It; ++It)
    {
        UClass* Class = *It;

        if(Class->HasAnyClassFlags(CLASS_Abstract))
        {
            continue;
        }

        if(Class->IsChildOf(UHoudiniNodeGenerator::StaticClass()))
        {
            UHoudiniNodeGenerator* Generator = NewObject<UHoudiniNodeGenerator>(GetTransientPackage(), Class, NAME_None, RF_Public | RF_Transactional);
            if(Generator)
            {
                Generators.Add(Generator);
            }
        }
    }

    return Generators.Num() > 0;
}


bool
FHoudiniNode::CreateObjectPackers()
{
    ObjectPackers.Empty();

    for(TObjectIterator<UClass> It; It; ++It)
    {
        UClass* Class = *It;

        if(Class->HasAnyClassFlags(CLASS_Abstract))
        {
            continue;
        }

        if(Class->IsChildOf(UHoudiniNodeObjectPacker::StaticClass()))
        {
            UHoudiniNodeObjectPacker* ObjectPacker = NewObject<UHoudiniNodeObjectPacker>(GetTransientPackage(), Class, NAME_None, RF_Public | RF_Transactional);
            if(ObjectPacker)
            {
                UClass* SupportedClass = ObjectPacker->GetSupportedClass();
                if(SupportedClass)
                {
                    ObjectPackers.Add(SupportedClass, ObjectPacker);
                }
            }
        }
    }

    return ObjectPackers.Num() > 0;
}


const TArray<UHoudiniNodeGenerator*>&
FHoudiniNode::GetGenerators() const
{
    return Generators;
}


const TMap<UClass*, UHoudiniNodeObjectPacker*>&
FHoudiniNode::GeObjectPackers() const
{
    return ObjectPackers;
}


IMPLEMENT_MODULE(FHoudiniNode, HoudiniNode);
