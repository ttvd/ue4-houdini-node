using UnrealBuildTool;
using System.IO;

namespace UnrealBuildTool.Rules
{
    public class HoudiniNodeEditor : ModuleRules
    {
        public HoudiniNodeEditor(ReadOnlyTargetRules Target) : base(Target)
        {
            string HoudiniVersion = "16.5.323";
            string HFSPath = "C:/Program Files/Side Effects Software/Houdini " + HoudiniVersion;
            string HDKIncludePath = HFSPath + "/toolkit/include";
            string HDKLibPath = HFSPath + "/custom/houdini/dsolib";
            string HDKBinPath = HFSPath + "/bin";


            /*
             * -DWIN32
        -DI386
        -nologo
        -TP
        -Zc:forScope
        -DSWAP_BITFIELDS
        -D_WIN32_WINNT=0x0502
        -DNOMINMAX
        -DSTRICT
        -DWIN32_LEAN_AND_MEAN
        -D_USE_MATH_DEFINES
        -D_CRT_SECURE_NO_DEPRECATE
        -D_CRT_NONSTDC_NO_DEPRECATE
        -D_SCL_SECURE_NO_WARNINGS
        -DBOOST_ALL_NO_LIB

        -wd4355
        -w14996
        #-O2
        -DNDEBUG
        -MD
        -EHsc
        -GR
        -bigobj
        */

            bUseRTTI = true;

            Definitions.Add("SIZEOF_VOID_P=8");
            Definitions.Add("_USE_MATH_DEFINES");
            Definitions.Add("HBOOST_ALL_NO_LIB");
            //Definitions.Add("/Ze");

            /*
            Definitions.Add("/GR");
            Definitions.Add("-EHsc");
            Definitions.Add("-w14996");
            Definitions.Add("-wd4355");
            Definitions.Add("SWAP_BITFIELDS");
            Definitions.Add("_WIN32_WINNT=0x0502");
            Definitions.Add("NOMINMAX");
            Definitions.Add("STRICT");
            Definitions.Add("_USE_MATH_DEFINES");
            

            Definitions.Add("AMD64");
            
            Definitions.Add("SESI_LITTLE_ENDIAN");
            Definitions.Add("FBX_ENABLED=1");
            Definitions.Add("OPENCL_ENABLED=1");
            Definitions.Add("OPENVDB_ENABLED=1");
            Definitions.Add("_REENTRANT");
            Definitions.Add("_FILE_OFFSET_BITS=64");
            */

            PrivateIncludePaths.AddRange(
				new string[]
				{
					"HoudiniNodeEditor/Private",
                    "HoudiniNode/Private"
                }
			);

			PublicIncludePaths.AddRange(
				new string[]
				{
					"HoudiniNodeEditor/Public",
                    "HoudiniNode/Public"
                }
			);

            PublicIncludePaths.Add(HDKIncludePath);
            PublicLibraryPaths.Add(HDKLibPath);
            PublicLibraryPaths.Add(HDKBinPath);

            string[] HDKLibs = { "libMOT", "libUT", "libSYS", "libOP", "libPI", "libPRM", "libOBJ", "libSOP", "libGU", "libGA", "hboost_system-mt" };
            foreach (string HDKLib in HDKLibs)
            {
                //string HDKLibFile = HDKLib + ".lib";
                //PublicAdditionalLibraries.Add(HDKLibFile);

                //string HDKLibDll = HDKLibFile + ".dll";
                //PublicDelayLoadDLLs.Add(HDKLibDll);
            }

            PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					"CoreUObject",
                    "Engine",
                    "HoudiniNode",
                    "PropertyEditor",
                    "Slate"
                }
			);

            if(Target.bBuildEditor == true)
            //if (UEBuildConfiguration.bBuildEditor == true)
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
