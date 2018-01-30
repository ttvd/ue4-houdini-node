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
    /*
    {
        const int32 MaxPathSize = 32768;
        FString Path = FString::ChrN(MaxPathSize, TEXT('\0'));
        FPlatformMisc::GetEnvironmentVariable(TEXT("PATH"), Path.GetCharArray().GetData(), MaxPathSize);

        const TCHAR* PathDelimiter = FPlatformMisc::GetPathVarDelimiter();

        TArray<FString> PathVars;
        Path.ParseIntoArray(PathVars, PathDelimiter, true);

        TArray<FString> ModifiedPathVars;

        for(int32 Idx = 0; Idx < PathVars.Num(); ++Idx)
        {
            // Blacklist anything Houdini, for now.

            const FString& PathEntry = PathVars[Idx];
            if(!PathEntry.Contains(TEXT("houdini"), ESearchCase::IgnoreCase))
            {
                ModifiedPathVars.Add(PathEntry);
            }
        }

        ModifiedPathVars.Add(TEXT("C:\\Program Files\\Side Effects Software\\Houdini 16.5.323\\bin"));

        FString ModifiedPath = FString::Join(ModifiedPathVars, PathDelimiter);
        FPlatformMisc::SetEnvironmentVar(TEXT("PATH"), *ModifiedPath);
    }
    */

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
        /*
        Director->resetForNewFile();
        Director->runPostNewScript();
        */
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


MOT_Director*
FHoudiniNode::GetDirector() const
{
    return Director;
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
