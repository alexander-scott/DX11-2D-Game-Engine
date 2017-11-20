#pragma once

#include <vector>

#include "IEMath.h"
#include "ColliderComponent.h"

class PhysicsManager
{
public:
	struct Collision 
	{
		Collision(ColliderComponent* a, ColliderComponent* b) : objA(a), objB(b)
		{

		}

		ColliderComponent* objA;
		ColliderComponent* objB;
	};

	PhysicsManager();
	~PhysicsManager();

	void AddCollider(ColliderComponent* go);

	void CheckCollisions();

private:
	bool CheckCollision(Collision col);
	void ResolveCollisions(std::vector<Collision> collisions);

	std::vector<ColliderComponent*>			_colliders;
};

