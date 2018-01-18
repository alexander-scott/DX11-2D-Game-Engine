#pragma once

#include "ObjectManager.h"
#include "PhysicsManager.h"

using namespace std;

class GameLevel
{
public:
	GameLevel(float startScore);
	~GameLevel();

	void Update(float deltaTime);
	void Draw();

	LevelState GetLevelState() { return mLevelState; }
	float& GetScore() { return mScore; }

	void CacheComponents(shared_ptr<GameObject> gameObj);

	void ConstructLevel(LevelData levelData);
	void ConstructionComplete();

	shared_ptr<GameObject> FindGameObject(std::string tag);

private:
	void RegisterFinishFlag();

	PhysicsManager										mPhysicsManager;
	LevelData											mLevelData;

	LevelState											mLevelState;
	TriggerBoxComponent*								mFinishFlagTrigger;

	vector<shared_ptr<GameObject>>						mRenderLayer0;
	vector<shared_ptr<GameObject>>						mRenderLayer1;
	vector<shared_ptr<GameObject>>						mRenderLayer2;
	vector<shared_ptr<GameObject>>						mRenderLayer3;

	vector<shared_ptr<GameObject>>						mGameObjects;
	map<shared_ptr<GameObject>, DamageableComponent*>	mDamageableGameObjects;

	float												mScore;
};