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
		ProjectilePoolObj(GameObject* obj, ProjectileComponent* proj) : 
			GameObject(obj), ProjectileComponent(proj) { }

		GameObject* GameObject;
		ProjectileComponent* ProjectileComponent;
	};

	~ProjectileManagerComponent();

	void AddCreatedGameObject(GameObject* go);
	void AddCreatedGameObjects(std::vector<GameObject*> goameObjects);

	// Get a gameobject from the pool
	GameObject* GetGameObject();
	GameObject* GetGameObject(std::string affectedTag, float damage);

	// Get a vector of gameobjects from the pool
	std::vector<GameObject*> GetAllInactiveGameObjects();
	std::vector<GameObject*> GetAllActiveGameObjects();

	// Update all active projectiles
	virtual void Update(float deltaTime) override;

	// Draw all active projectiles
	virtual void Draw(ICamera* cam) override;

private:
	std::vector<ProjectilePoolObj>	mActiveGameObjects;
	std::vector<ProjectilePoolObj>	mInactiveGameObjects;
};