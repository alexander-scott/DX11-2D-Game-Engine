#pragma once

#include "GameObject.h"
#include "ProjectileComponent.h"

#include "IComponent.h"
#include "IUpdateable.h"

class ProjectileManagerComponent : public IComponent, public IUpdateable
{
public:
	struct ProjectilePoolObj 
	{
	public:
		ProjectilePoolObj(GameObject* obj, ProjectileComponent* proj) : gameObject(obj), projectileComponent(proj) { }

		GameObject* gameObject;
		ProjectileComponent* projectileComponent;
	};

	~ProjectileManagerComponent();

	void AddCreatedGameObject(GameObject* go);

	GameObject* GetGameObject();
	GameObject* GetGameObject(std::string affectedTag, float damage);
	virtual void Update(float deltaTime) override;

private:
	std::vector<ProjectilePoolObj>	_activeGameObjects;
	std::vector<ProjectilePoolObj>	_inactiveGameObjects;
};