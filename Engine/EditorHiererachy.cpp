#include "EditorHiererachy.h"

int EditorHierarchy::GetGameObjectCount(void* enginePtr)
{
	return static_cast<Engine*>(enginePtr)->GetScene()->GetNumberOfGameObjects();
}

EditorHierarchy::HierarchyItem* EditorHierarchy::PopulateHierarchyItems(void* enginePtr, int itemCount)
{
	auto scene = static_cast<Engine*>(enginePtr)->GetScene();

	HierarchyItem* items = new HierarchyItem[itemCount];
	for (int i = 0; i < itemCount; i++)
	{
		auto gameObj = scene->GetGameObjectAtIndex(i);

		items[i].GameObjectID = gameObj->GetID(); // Set GameObject ID

		auto parentGO = gameObj->GetParent();
		if (parentGO == nullptr) // If the GameObject doesn't have a parent set ID to NULL
			items[i].GameObjectParentID = NULL;
		else // If the GameObject does have a parent set the parent ID to the parent GameObject's ID
			items[i].GameObjectParentID = parentGO->GetID();

		char* result = new char[gameObj->GetTag().length() + 1];
		strcpy_s(result, gameObj->GetTag().length() + 1, gameObj->GetTag().c_str());
		items[i].GameObjectName = result; // Set the GameObject's name
	}

	return items;
}

void EditorHierarchy::FreeHierarchyMemory(void * hierarchy)
{
	delete hierarchy;
}
