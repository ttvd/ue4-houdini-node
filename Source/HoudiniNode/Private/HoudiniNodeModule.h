#include "HoudiniNodeModuleInterface.h"

class FHoudiniNodeModule : public IHoudiniNodeModuleInterface
{
	public:

		~FHoudiniNodeModule();
		
	public:

		virtual void StartupModule() override;
};
