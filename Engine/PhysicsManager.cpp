#include "PhysicsManager.h"



PhysicsManager::PhysicsManager()
{
}


PhysicsManager::~PhysicsManager()
{
}

void PhysicsManager::AddCollider(ColliderComponent * go)
{
	_colliders.push_back(go);
}

void PhysicsManager::CheckCollisions()
{
	std::vector<Collision> collisions;

	for (int i = 0; i < _colliders.size(); i++)
	{
		for (int j = i + 1; j < _colliders.size(); j++)
		{
			Collision col(_colliders[i], _colliders[j]);
			if (CheckCollision(col))
			{
				collisions.push_back(col);
			}
		}
	}

	if (collisions.size() > 0)
	{
		ResolveCollisions(collisions);
	}
}

bool PhysicsManager::CheckCollision(Collision col)
{
	return false;
}

void PhysicsManager::ResolveCollisions(std::vector<Collision> collisions)
{

	//// Calculate relative velocity
	//Vec2 rv = col.objB->GetRigidbodyComponent()->velocity - col.objA->GetRigidbodyComponent()->velocity;

	//// Calculate relative velocity in terms of the normal direction
	//float velAlongNormal = Dot(rv, normal);

	//// Do not resolve if velocities are separating
	//if (velAlongNormal > 0)
	//	return;

	//// Calculate restitution
	//float e = min(col.objA->GetRigidbodyComponent()->restitution, col.objB->GetRigidbodyComponent()->restitution);

	//// Calculate impulse scalar
	//float j = -(1 + e) * velAlongNormal;
	//j /= 1 / col.objA->GetRigidbodyComponent()->m + 1 / col.objB->GetRigidbodyComponent()->m;

	//// Apply impulse
	//Vec2 impulse = j * normal;
	//col.objA->GetRigidbodyComponent()->velocity -= 1 / col.objA->GetRigidbodyComponent()->m * impulse;
	//col.objB->GetRigidbodyComponent()->velocity += 1 / col.objB->GetRigidbodyComponent()->m * impulse;
}
