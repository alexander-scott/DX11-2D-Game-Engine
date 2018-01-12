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
		ProjectilePoolObj(shared_ptr<GameObject> obj, ProjectileComponent* proj) :
			GameObject(obj), ProjectileComponent(proj) { }

		shared_ptr<GameObject> GameObject;
		ProjectileComponent* ProjectileComponent;
	};

	~ProjectileManagerComponent();

	void AddCreatedGameObject(shared_ptr<GameObject> go);
	void AddCreatedGameObjects(std::vector<shared_ptr<GameObject>> goameObjects);

	// Get a gameobject from the pool
	shared_ptr<GameObject> GetGameObject();
	shared_ptr<GameObject> GetGameObject(std::string affectedTag, float damage);

	// Get a vector of gameobjects from the pool
	std::vector<shared_ptr<GameObject>> GetAllInactiveGameObjects();
	std::vector<shared_ptr<GameObject>> GetAllActiveGameObjects();

	// Update all active projectiles
	virtual void Update(float deltaTime) override;

	// Draw all active projectiles
	virtual void Draw(ICamera* cam) override;

private:
	std::vector<ProjectilePoolObj>	mActiveGameObjects;
	std::vector<ProjectilePoolObj>	mInactiveGameObjects;
};