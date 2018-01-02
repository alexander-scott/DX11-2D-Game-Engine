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

	ObjectGrid*								mObjectGrid;

	std::vector<GameObject*>				mGameObjects;
	std::vector<ColliderComponent*>			mColliders;
	std::vector<Collision>					mContacts;
};

