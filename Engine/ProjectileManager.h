#pragma once

#include "GameObject.h"
#include "ProjectileComponent.h"

#include "IComponent.h"
#include "IUpdateable.h"

class ProjectileManager : public IComponent, public IUpdateable
{
public:
	struct ProjectilePoolObj 
	{
	public:
		ProjectilePoolObj(GameObject* obj, ProjectileComponent* proj) : gameObject(obj), projectileComponent(proj) { }

		GameObject* gameObject;
		ProjectileComponent* projectileComponent;
	};

	~ProjectileManager();

	void AddCreatedGameObject(GameObject* go);

	GameObject* GetGameObject();
	virtual void Update(float deltaTime) override;

private:
	std::vector<ProjectilePoolObj>	_activeGameObjects;
	std::vector<ProjectilePoolObj>	_inactiveGameObjects;
};