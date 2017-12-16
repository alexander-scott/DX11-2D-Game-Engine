#pragma once

#include "GameObject.h"
#include "ProjectileComponent.h"

#include <vector>

class ProjectileManager
{
public:
	struct ProjectilePoolObj 
	{
	public:
		ProjectilePoolObj(GameObject* obj, ProjectileComponent* proj) : gameObject(obj), projectileComponent(proj) { }

		GameObject* gameObject;
		ProjectileComponent* projectileComponent;
	};

	ProjectileManager(int numToCreate);
	~ProjectileManager();

	GameObject* GetGameObject();
	void Update(float deltaTime);

private:
	std::vector<ProjectilePoolObj>	_activeGameObjects;
	std::vector<ProjectilePoolObj>	_inactiveGameObjects;
};