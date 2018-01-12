#include "ProjectileManagerComponent.h"

ProjectileManagerComponent::~ProjectileManagerComponent()
{
	for (auto& g : mActiveGameObjects)
	{
		g.GameObject = nullptr;
	}

	for (auto& g : mInactiveGameObjects)
	{
		g.GameObject = nullptr;
	}
}

void ProjectileManagerComponent::AddCreatedGameObject(shared_ptr<GameObject> go)
{
	ProjectilePoolObj obj(go, go->GetComponent<ProjectileComponent>());
	obj.GameObject->SetActive(false);
	mInactiveGameObjects.push_back(obj);
}

void ProjectileManagerComponent::AddCreatedGameObjects(std::vector<shared_ptr<GameObject>> gameObjects)
{
	for (auto& go : gameObjects)
	{
		ProjectilePoolObj obj(go, go->GetComponent<ProjectileComponent>());
		obj.GameObject->SetActive(false);
		mInactiveGameObjects.push_back(obj);
	}
}

shared_ptr<GameObject> ProjectileManagerComponent::GetGameObject()
{
	if (mInactiveGameObjects.size() > 0)
	{
		ProjectilePoolObj obj = mInactiveGameObjects[0];
		mActiveGameObjects.push_back(mInactiveGameObjects[0]);
		mInactiveGameObjects.erase(mInactiveGameObjects.begin());

		// SET ACTIVE
		obj.GameObject->SetActive(true);
		obj.ProjectileComponent->Reset();

		return obj.GameObject;
	}
	else
	{
		throw;

		return nullptr;
	}
}

shared_ptr<GameObject> ProjectileManagerComponent::GetGameObject(std::string affectedTag, float damage)
{
	if (mInactiveGameObjects.size() > 0)
	{
		ProjectilePoolObj obj = mInactiveGameObjects[0];
		mActiveGameObjects.push_back(mInactiveGameObjects[0]);
		mInactiveGameObjects.erase(mInactiveGameObjects.begin());

		// SET ACTIVE
		obj.GameObject->SetActive(true);
		obj.ProjectileComponent->Reset(affectedTag, damage);

		return obj.GameObject;
	}
	else
	{
		throw;

		return nullptr;
	}
}

void ProjectileManagerComponent::Update(float deltaTime)
{
	for (int i = 0; i < mActiveGameObjects.size(); i++)
	{
		if (mActiveGameObjects[i].ProjectileComponent->IsDead())
		{
			ProjectilePoolObj obj = mActiveGameObjects[i];
			mInactiveGameObjects.push_back(obj);
			mActiveGameObjects.erase(mActiveGameObjects.begin() + i);

			// SET INACTIVE
			obj.GameObject->SetActive(false);
		}
		else
		{
			mActiveGameObjects[i].ProjectileComponent->Update(deltaTime);
		}
	}
}

void ProjectileManagerComponent::Draw(ICamera* cam)
{
	for (auto go : mActiveGameObjects)
	{
		go.GameObject->Draw(cam);
	}
}

std::vector<shared_ptr<GameObject>> ProjectileManagerComponent::GetAllInactiveGameObjects()
{
	std::vector<shared_ptr<GameObject>> objs;
	for (auto go : mInactiveGameObjects)
	{
		objs.push_back(go.GameObject);
	}
	return objs;
}

std::vector<shared_ptr<GameObject>> ProjectileManagerComponent::GetAllActiveGameObjects()
{
	std::vector<shared_ptr<GameObject>> objs;
	for (auto go : mActiveGameObjects)
	{
		objs.push_back(go.GameObject);
	}
	return objs;
}
