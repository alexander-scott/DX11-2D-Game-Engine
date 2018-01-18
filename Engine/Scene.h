#pragma once

#include "ObjectManager.h"
#include "PhysicsManager.h"

using namespace std;

class Scene
{
public:
	Scene();
	~Scene();

	void Update(float deltaTime);
	void Draw();

	void CacheComponents(shared_ptr<GameObject> gameObj);

	void SetupPhysics(LevelData levelData);

private:
	PhysicsManager										mPhysicsManager;
	LevelData											mLevelData;

	TriggerBoxComponent*								mFinishFlagTrigger;

	vector<shared_ptr<GameObject>>						mRenderLayer0;
	vector<shared_ptr<GameObject>>						mRenderLayer1;
	vector<shared_ptr<GameObject>>						mRenderLayer2;
	vector<shared_ptr<GameObject>>						mRenderLayer3;

	vector<shared_ptr<GameObject>>						mGameObjects;
	map<shared_ptr<GameObject>, DamageableComponent*>	mDamageableGameObjects;
};