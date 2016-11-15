#include "HoudiniNodePrivatePCH.h"
#include "HoudiniNodeModule.h"


void
FHoudiniNodeModule::StartupModule()
{
	FModuleManager::LoadModuleChecked<IHoudiniNodeModuleInterface>("HoudiniNode");
}


FHoudiniNodeModule::~FHoudiniNodeModule()
{
	
}


IMPLEMENT_MODULE(FHoudiniNodeModule, HoudiniNode);
