#pragma once
#include "HoudiniNodeModuleInterface.h"

class HOUDININODE_API FHoudiniNodeModule : public IHoudiniNodeModuleInterface
{
	public:

		~FHoudiniNodeModule();
		
	public:

		virtual void StartupModule() override;
};
