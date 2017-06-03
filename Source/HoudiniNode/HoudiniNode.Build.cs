using UnrealBuildTool;
using System.IO;

namespace UnrealBuildTool.Rules
{
	public class HoudiniNode : ModuleRules
	{
		public HoudiniNode(TargetInfo Target)
		{
			PrivateIncludePaths.AddRange(
				new string[]
				{
					"HoudiniNode/Private"
				}
			);

			PublicIncludePaths.AddRange(
				new string[]
				{
					"HoudiniNode/Public"
				}
			);

			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					"CoreUObject",
                    "Engine",
                }
			);

            if(UEBuildConfiguration.bBuildEditor == true)
            {
                PublicDependencyModuleNames.AddRange(
                    new string[]
                    {
                        "AssetTools",
                        "UnrealEd",
                        "TargetPlatform",
                        "Settings",
                    }
                );
            }

        }
	}
}
