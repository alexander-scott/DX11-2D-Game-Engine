#include "ProjectileManager.h"

#include "SetActiveMessage.h"

ProjectileManager::~ProjectileManager()
{
	for (auto g : _activeGameObjects)
	{
		delete g.gameObject;
	}

	for (auto g : _inactiveGameObjects)
	{
		delete g.gameObject;
	}
}

void ProjectileManager::AddCreatedGameObject(GameObject * go)
{
	ProjectilePoolObj obj(go, go->GetComponent<ProjectileComponent>());
	SetActiveMessage activeMsg(true);
	obj.gameObject->SendMessageToComponents(activeMsg);
	_inactiveGameObjects.push_back(obj);
}

GameObject * ProjectileManager::GetGameObject()
{
	if (_inactiveGameObjects.size() > 0)
	{
		ProjectilePoolObj obj = _inactiveGameObjects[0];
		_activeGameObjects.push_back(_inactiveGameObjects[0]);
		_inactiveGameObjects.erase(_inactiveGameObjects.begin());

		// SET ACTIVE
		SetActiveMessage activeMsg(true);
		obj.gameObject->SendMessageToComponents(activeMsg);

		return obj.gameObject;
	}
	else
	{
		throw;

		return nullptr;
	}
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
			SetActiveMessage activeMsg(false);
			obj.gameObject->SendMessageToComponents(activeMsg);
		}
	}
}
