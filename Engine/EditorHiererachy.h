#pragma once

#include "EditorInterface.h"
#include <stdio.h>

namespace EditorHierarchy
{
	struct HierarchyItem
	{
		int GameObjectID;
		int GameObjectParentID;
		char* GameObjectName;
	};

	extern "C" { DllExport int GetGameObjectCount(void* enginePtr); }

	extern "C" { DllExport HierarchyItem* PopulateHierarchyItems(void* enginePtr, int itemCount); }
}
