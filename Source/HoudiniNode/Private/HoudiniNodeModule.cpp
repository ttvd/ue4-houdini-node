#include "HoudiniNodePrivatePCH.h"
#include "HoudiniNodeModule.h"


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


IMPLEMENT_MODULE(FHoudiniNode, HoudiniNode);
