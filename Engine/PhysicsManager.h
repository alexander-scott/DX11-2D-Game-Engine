#pragma once

#include <vector>

#include "IEMath.h"
#include "ColliderComponent.h"
#include "Manifold.h"

class PhysicsManager
{
public:
	PhysicsManager();
	~PhysicsManager();

	void AddCollider(ColliderComponent* go);

	void Update(float deltaTime);

private:
	void IntegrateForces(ColliderComponent* go, float deltaTime);
	void IntegrateVelocity(ColliderComponent* go, float deltaTime);

	std::vector<ColliderComponent*>			_colliders;
	std::vector<Manifold>					_contacts;
};

