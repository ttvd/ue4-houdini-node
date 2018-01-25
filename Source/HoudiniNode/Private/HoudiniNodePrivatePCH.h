#pragma once

#if WITH_EDITOR
#include "UnrealEd.h"
#endif

#include "Core.h"
#include "CoreUObject.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"


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
#pragma warning(disable : 4307)
#pragma warning(disable : 4308)
#pragma warning(disable : 4706)

#include <SYS/SYS_Version.h>

#include <UT/UT_UndoManager.h>
#include <UT/UT_String.h>
#include <UT/UT_Version.h>

#include <MOT/MOT_Director.h>
#include <PI/PI_ResourceManager.h>

#include <OP/OP_Network.h>
#include <OBJ/OBJ_Node.h>

#include <GU/GU_Detail.h>
#include <OP/OP_Context.h>
#include <SOP/SOP_Node.h>

#pragma warning(pop)

#ifndef LOCTEXT_NAMESPACE
#define LOCTEXT_NAMESPACE "HoudiniNode"
#endif

#define HOUDINI_NODE_ATTRIBUTE_PART                 TEXT("houdini_node_part")

