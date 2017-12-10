#pragma once

#include <vector>

#include "IEMath.h"
#include "ColliderComponent.h"
#include "GameObject.h"
#include "Manifold.h"

class PhysicsManager
{
public:
	PhysicsManager();
	~PhysicsManager();

	void AddCollider(GameObject* gameObject, ColliderComponent* collider);

	void Update(float deltaTime);

private:
	void IntegrateForces(ColliderComponent* collider, float deltaTime);
	void IntegrateVelocity(ColliderComponent* collider, float deltaTime);

	std::vector<GameObject*>				_gameObjects;
	std::vector<ColliderComponent*>			_colliders;
	std::vector<Manifold>					_contacts;
};

