#pragma once

#include "EditorInterface.h"

namespace EditorHierarchy
{
	struct HierarchyItem
	{
		char GameObjectName[100];
		int GameObjectID;
		int GameObjectParentID;
	};

	extern "C" { DllExport int GetGameObjectCount(void* enginePtr); }

	extern "C" { DllExport void __cdecl PopulateHierarchyItems(void* enginePtr, struct HierarchyItem* items, int itemCount); }
}
