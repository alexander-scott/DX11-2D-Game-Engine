#pragma once

#include <vector>

#include "IEMath.h"
#include "ColliderComponent.h"
#include "GameObject.h"
#include "Collision.h"
#include "ObjectGrid.h"

class PhysicsManager
{
public:
	~PhysicsManager();

	void BuildGrid(int levelWidth, int levelHeight);
	void AddCollider(GameObject* gameObject, ColliderComponent* collider);

	void Update(float deltaTime);

private:
	void IntegrateForces(ColliderComponent* collider, float deltaTime);
	void IntegrateVelocity(ColliderComponent* collider, float deltaTime);

	ObjectGrid*								_objectGrid;

	std::vector<GameObject*>				_gameObjects;
	std::vector<ColliderComponent*>			_colliders;
	std::vector<Collision>					_contacts;
};

