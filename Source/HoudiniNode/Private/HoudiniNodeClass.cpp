#include "HoudiniNodePrivatePCH.h"
#include "HoudiniNodeClass.h"
#include "HoudiniNodeModule.h"


UHoudiniNodeClass::UHoudiniNodeClass(const FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer),
    HoudiniNodeAsset(nullptr),
    Library(nullptr),
    Node(nullptr)
{

}


UHoudiniNodeClass::~UHoudiniNodeClass()
{
    RemoveLibrary();
}


bool
UHoudiniNodeClass::AddLibrary()
{
    if(!HoudiniNodeAsset)
    {
        return false;
    }

    UT_String RawFilename("");
    if(!HoudiniNodeAsset->GetFilename(RawFilename))
    {
        return false;
    }

    if(!OPgetDirector())
    {
        return false;
    }

    OP_OTLManager& Manager = OPgetDirector()->getOTLManager();
    UT_WorkBuffer WorkBuffer;

    Library = Manager.addLibrary(RawFilename.c_str(), OTL_INTERNAL_META, true, false, WorkBuffer);

    return Library != nullptr;
}


bool
UHoudiniNodeClass::RemoveLibrary()
{
    if(!HoudiniNodeAsset)
    {
        return false;
    }

    if(!HasLibrary())
    {
        return false;
    }

    UT_String RawFilename("");
    if(!HoudiniNodeAsset->GetFilename(RawFilename))
    {
        return false;
    }

    if(!OPgetDirector())
    {
        return false;
    }

    OP_OTLManager& Manager = OPgetDirector()->getOTLManager();
    Manager.removeLibrary(RawFilename.c_str(), "", false);

    Library = nullptr;

    return true;
}


bool
UHoudiniNodeClass::HasLibrary() const
{
    return Library != nullptr;
}


bool
UHoudiniNodeClass::GetAssetNames(TArray<UT_String>& AssetNames) const
{
    AssetNames.Empty();

    if(!HasLibrary())
    {
        return false;
    }

    const int32 DefitionsNum = Library->getNumDefinitions();
    for(int32 Idx = 0; Idx < DefitionsNum; ++Idx)
    {
        const OP_OTLDefinition& Definition = Library->getDefinition(Idx);
        //const UT_String& RawAssetName = Definition.getName();
        const UT_String& RawAssetName = Definition.getOpTableName();

        //FString AssetName = UTF8_TO_TCHAR(RawAssetName.c_str());
        AssetNames.Add(RawAssetName);
    }

    return AssetNames.Num() > 0;
}
