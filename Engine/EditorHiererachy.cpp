#include "EditorHiererachy.h"

int EditorHierarchy::GetGameObjectCount(void* enginePtr)
{
	return static_cast<Engine*>(enginePtr)->GetScene()->GetNumberOfGameObjects();
}

EditorHierarchy::HierarchyItem* EditorHierarchy::PopulateHierarchyItems(void* enginePtr, int itemCount)
{
	auto scene = static_cast<Engine*>(enginePtr)->GetScene();

	static HierarchyItem* items = new HierarchyItem[itemCount];
	for (int i = 0; i < itemCount; i++)
	{
		auto gameObj = scene->GetGameObjectAtIndex(i);

		items[i].GameObjectID = gameObj->GetID();
		items[i].GameObjectParentID = 0;

		char* result = new char[gameObj->GetTag().length() + 1];
		strcpy_s(result, gameObj->GetTag().length() + 1, gameObj->GetTag().c_str());

		items[i].GameObjectName = result;
		//items[itemCount].GameObjectID = gameObj->GetID();
		//strncpy_s(items[itemCount].GameObjectName, gameObj->GetTag().c_str(), sizeof(items[itemCount].GameObjectName));
		//items[itemCount].GameObjectParentID = -1;
	}

	return items;
}