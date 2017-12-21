#pragma once

#include "GameObject.h"
#include "ProjectileComponent.h"

#include "IComponent.h"
#include "IUpdateable.h"
#include "IDrawable.h"

class ProjectileManagerComponent : public IComponent, public IUpdateable, public IDrawable
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
	void AddCreatedGameObjects(std::vector<GameObject*> goameObjects);

	GameObject* GetGameObject();
	GameObject* GetGameObject(std::string affectedTag, float damage);

	std::vector<GameObject*> GetAllInactiveGameObjects();
	std::vector<GameObject*> GetAllActiveGameObjects();

	virtual void Update(float deltaTime) override;
	virtual void Draw(ICamera* cam) override;

private:
	std::vector<ProjectilePoolObj>	_activeGameObjects;
	std::vector<ProjectilePoolObj>	_inactiveGameObjects;
};