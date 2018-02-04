#pragma once

#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInterface.h"
#include "Engine/StaticMeshActor.h"
#include "AssetRegistryModule.h"
#include "Misc/CoreMisc.h"

#if WITH_EDITOR
#include "EditorFramework/AssetImportData.h"
#include "Interfaces/ITargetPlatform.h"
#include "Interfaces/ITargetPlatformManagerModule.h"
#include "RawMesh.h"
#endif

#pragma warning(push)
#pragma warning(disable : 4211)
#pragma warning(disable : 4018)
#pragma warning(disable : 4800)
#pragma warning(disable : 4499)
#pragma warning(disable : 4996)
#pragma warning(disable : 4946)
#pragma warning(disable : 4146)
#pragma warning(disable : 4396)
#pragma warning(disable : 4457)
#pragma warning(disable : 4706)
#pragma warning(disable : 4307)
#pragma warning(disable : 4308)
#pragma warning(disable : 4103)
#pragma warning(disable : 4668)
#pragma warning(disable : 4191)

#include <SYS/SYS_Version.h>

#include <UT/UT_UndoManager.h>
#include <UT/UT_String.h>
#include <UT/UT_Version.h>

#include <MOT/MOT_Director.h>
#include <PI/PI_ResourceManager.h>

#include <OP/OP_Network.h>
#include <OP/OP_Operator.h>
#include <OP/OP_OTLLibrary.h>
#include <OP/OP_Context.h>

#include <PRM/PRM_Name.h>
#include <PRM/PRM_Template.h>
#include <PRM/PRM_Range.h>

#include <OBJ/OBJ_Node.h>
#include <SOP/SOP_Node.h>

#include <GU/GU_Detail.h>
#include <GU/GU_DetailHandle.h>

#pragma warning(pop)

#ifndef LOCTEXT_NAMESPACE
#define LOCTEXT_NAMESPACE "HoudiniNode"
#endif


#define HOUDINI_NODE_ATTRIBUTE_PART                 TEXT("part")
#define HOUDINI_NODE_ATTRIBUTE_GENERATOR_PRIM       TEXT("generator_prim")
#define HOUDINI_NODE_ATTRIBUTE_GENERATOR_POINT      TEXT("generator_point")



