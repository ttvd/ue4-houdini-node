#include "HoudiniNodeClass.h"
#include "HoudiniNodePrivatePCH.h"
#include "HoudiniNodeModule.h"
#include "HoudiniNodeAsset.h"


UHoudiniNodeClass::UHoudiniNodeClass(const FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer),
    HoudiniNodeAsset(nullptr),
    Library(nullptr),
    LibraryPath(TEXT("")),
    Node(nullptr)
{

}


UHoudiniNodeClass::~UHoudiniNodeClass()
{
	DestroyNode();
    RemoveLibrary();
}


bool
UHoudiniNodeClass::AddLibrary()
{
    MOT_Director* Director = GHoudiniNode->GetDirector();
    if(!Director)
    {
        return false;
    }

    if(!HoudiniNodeAsset)
    {
        return false;
    }

    FString Filename(TEXT(""));
    if(!HoudiniNodeAsset->GetFilename(Filename))
    {
        return false;
    }

    OP_OTLManager& Manager = Director->getOTLManager();
    UT_WorkBuffer WorkBuffer;

    UT_String RawFilename = TCHAR_TO_UTF8(*Filename);

    Library = Manager.addLibrary(RawFilename.c_str(), OTL_INTERNAL_META, true, false, WorkBuffer);
    if(Library)
    {
        LibraryPath = Filename;
		return true;
    }

    return false;
}


bool
UHoudiniNodeClass::RemoveLibrary()
{
    MOT_Director* Director = GHoudiniNode->GetDirector();
    if(!Director)
    {
        return false;
    }

    if(!HoudiniNodeAsset)
    {
        return false;
    }

    if(!HasLibrary())
    {
        return false;
    }

    OP_OTLManager& Manager = Director->getOTLManager();

    UT_String RawFilename = TCHAR_TO_UTF8(*LibraryPath);
    Manager.removeLibrary(RawFilename.c_str(), "", false);

    Library = nullptr;
    LibraryPath = TEXT("");

    return true;
}


bool
UHoudiniNodeClass::HasLibrary() const
{
    if(Library && !LibraryPath.IsEmpty())
    {
        return true;
    }

    return false;
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
        const UT_String& RawAssetName = Definition.getName();
        AssetNames.Add(RawAssetName);
    }

    return AssetNames.Num() > 0;
}


bool
UHoudiniNodeClass::CreateNode()
{
	TArray<UT_String> AssetNames;
    if(GetAssetNames(AssetNames))
	{
		const UT_String& AssetName = AssetNames[0];
		return CreateNode(AssetName);
	}

	return false;
}


bool
UHoudiniNodeClass::CreateNode(const UT_String& NodeName)
{
	if(!NodeName.isstring())
	{
		return false;
	}

	if(Node)
	{
		return false;
	}

	OP_Network* ObjNetwork = GHoudiniNode->GetObjNetwork();
	if(!ObjNetwork)
	{
		return false;
	}

	Node = (OBJ_Node*) ObjNetwork->createNode(NodeName.c_str());
	if(!Node)
	{
		return false;
	}

	Node->runCreateScript();

	return true;
}


bool
UHoudiniNodeClass::DestroyNode()
{
	if(!Node)
	{
		return false;
	}

	OP_Network* ObjNetwork = GHoudiniNode->GetObjNetwork();
	if(!ObjNetwork)
	{
		return false;
	}

	ObjNetwork->destroyNode(Node);
	Node = nullptr;

	return true;
}


OBJ_Node*
UHoudiniNodeClass::GetNode() const
{
	return Node;
}
