#pragma once

#include <vector>
#include <set>

#include "Consts.h"
#include "ColliderComponent.h"
#include "GameObject.h"
#include "Collision.h"
#include "ObjectGrid.h"

using namespace std;

class PhysicsManager
{
public:
	~PhysicsManager();

	void BuildObjectGrid(int levelWidth, int levelHeight);
	void AddCollider(shared_ptr<GameObject> gameObject, ColliderComponent* collider);

	void Update(float deltaTime);

	bool GetSetup() { return mSetup; }

private:
	void IntegrateForces(ColliderComponent* collider, float deltaTime);
	void IntegrateVelocity(ColliderComponent* collider, float deltaTime);

	void UpdateObjectInGrid(ColliderComponent* collider, int colliderIndex);
	void GetIntersectingCells(std::set<int>& intersectingCells, ColliderComponent* collider);

	ObjectGrid*							mObjectGrid;

	vector<shared_ptr<GameObject>>		mGameObjects;
	vector<ColliderComponent*>			mColliders;

	bool								mSetup = false;
};

