#include "HoudiniNodeModule.h"
#include "HoudiniNodePrivatePCH.h"
#include "HoudiniNodeGenerator.h"


FHoudiniNode*
GHoudiniNode = nullptr;


FHoudiniNode::FHoudiniNode() :
    Director(nullptr)
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

    Director = new MOT_Director("HoudiniNode");
    ensure(Director);
    OPsetDirector(Director);
    PIcreateResourceManager();

    GHoudiniNode = this;

    CreateGenerators();
}


void
FHoudiniNode::ShutdownModule()
{
    if(Director)
    {
        Director->resetForNewFile();
        Director->runPostNewScript();

        Director = nullptr;
    }
}


OP_Network*
FHoudiniNode::GetObjNetwork() const
{
    if(Director)
    {
        return (OP_Network*) Director->getChild("obj");
    }

    return nullptr;
}


bool
FHoudiniNode::CreateGenerators()
{
    Generators.Empty();

    for(TObjectIterator<UClass> It; It; ++It)
    {
        if(It->HasAnyClassFlags(CLASS_Abstract))
        {
            continue;
        }

        if(It->IsChildOf(UHoudiniNodeGenerator::StaticClass()))
        {

        }
    }

    return Generators.Num() > 0;
}


IMPLEMENT_MODULE(FHoudiniNode, HoudiniNode);
