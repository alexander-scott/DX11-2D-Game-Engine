#include "ProjectileManager.h"

ProjectileManager::ProjectileManager(int numToCreate)
{
	for (int i = 0; i < numToCreate; i++)
	{

	}
}

ProjectileManager::~ProjectileManager()
{
}

GameObject * ProjectileManager::GetGameObject()
{
	if (_inactiveGameObjects.size() > 0)
	{
		ProjectilePoolObj obj = _inactiveGameObjects[0];
		_activeGameObjects.push_back(_inactiveGameObjects[0]);
		_inactiveGameObjects.erase(_inactiveGameObjects.begin());

		return obj.gameObject;
	}
	return nullptr;
}

void ProjectileManager::Update(float deltaTime)
{
	for (int i = 0; i < _activeGameObjects.size(); i++)
	{
		if (_activeGameObjects[i].projectileComponent->IsDead())
		{
			ProjectilePoolObj obj = _activeGameObjects[i];
			_inactiveGameObjects.push_back(obj);
			_activeGameObjects.erase(_activeGameObjects.begin() + i);

			// SET INACTIVE
		}
		else
		{
			_activeGameObjects[i].gameObject->Update(deltaTime);
		}
	}
}
