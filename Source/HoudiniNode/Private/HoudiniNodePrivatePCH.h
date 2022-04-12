#pragma once

#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInterface.h"
#include "Engine/StaticMeshActor.h"
#include "AssetRegistryModule.h"
#include "Misc/CoreMisc.h"
#include "Algo/Reverse.h"
#include "Engine/CollisionProfile.h"
#include "PhysicsEngine/BodyInstance.h"
#include "PhysicsEngine/BodySetup.h"
#include "Serialization/MemoryReader.h"
#include "Serialization/MemoryWriter.h"

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
#include <PRM/PRM_ChoiceList.h>

#include <OBJ/OBJ_Node.h>
#include <SOP/SOP_Node.h>

#include <GU/GU_Detail.h>
#include <GU/GU_DetailHandle.h>

#pragma warning(pop)

#ifndef LOCTEXT_NAMESPACE
#define LOCTEXT_NAMESPACE "HoudiniNode"
#endif

#define HOUDINI_NODE_DEFAULT_MATERIAL                                   TEXT("Material'/Engine/EngineMaterials/DefaultMaterial.DefaultMaterial'")

#define HOUDINI_NODE_ATTRIBUTE_NORMAL                                   TEXT("N")
#define HOUDINI_NODE_ATTRIBUTE_COLOR                                    TEXT("Cd")
#define HOUDINI_NODE_ATTRIBUTE_UV                                       TEXT("uv")
#define HOUDINI_NODE_ATTRIBUTE_MATERIAL                                 TEXT("material")

#define HOUDINI_NODE_ATTRIBUTE_PART                                     TEXT("part")
#define HOUDINI_NODE_ATTRIBUTE_PART_XFORM_T                             TEXT("part_xform_t")
#define HOUDINI_NODE_ATTRIBUTE_PART_XFORM_S                             TEXT("part_xform_s")
#define HOUDINI_NODE_ATTRIBUTE_PART_XFORM_R                             TEXT("part_xform_r")
#define HOUDINI_NODE_ATTRIBUTE_GENERATOR_PRIM                           TEXT("generator_prim")
#define HOUDINI_NODE_ATTRIBUTE_GENERATOR_POINT                          TEXT("generator_point")

#define HOUDINI_NODE_ATTRIBUTE_ASSIGN_COLLISION                         TEXT("assign_collision")

#define HOUDINI_NODE_ATTRIBUTE_ASSIGN_COLLISION_DEFAULT                 TEXT("UseDefault")
#define HOUDINI_NODE_ATTRIBUTE_ASSIGN_COLLISION_SIMPLE_AND_COMPLEX      TEXT("UseSimpleAndComplex")
#define HOUDINI_NODE_ATTRIBUTE_ASSIGN_COLLISION_SIMPLE_AS_COMPLEX       TEXT("UseSimpleAsComplex")
#define HOUDINI_NODE_ATTRIBUTE_ASSIGN_COLLISION_COMPLEX_AS_SIMPLE       TEXT("UseComplexAsSimple")

#define HOUDINI_NODE_ATTRIBUTE_ASSIGN_COLLISION_PROFILE                 TEXT("assign_collision_profile")

#define HOUDINI_NODE_PACKING_SECTION_OBJECTS                            TEXT("objects")
#define HOUDINI_NODE_PACKING_SECTION_DATA                               TEXT("data")
