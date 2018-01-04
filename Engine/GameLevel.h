#pragma once

#include "ObjectManager.h"
#include "PhysicsManager.h"

class GameLevel
{
public:
	GameLevel();
	~GameLevel();

	LevelState GetLevelState() { return mLevelState; }

	void CacheComponents(GameObject* gameObj, int renderLayer);

	void ConstructLevel(LevelData levelData);

	void PostBuildEvents();

	void Update(float deltaTime);
	void Draw();

	GameObject* FindGameObject(std::string tag);

	float											Score;

private:
	void SetupCamera();
	void RegisterFinishFlag();

	ObjectManager									mObjectManager;
	PhysicsManager									mPhysicsManager;
	LevelData										mLevelData;

	LevelState										mLevelState;
	TriggerBoxComponent*							mFinishFlagTrigger;

	std::vector<GameObject*>						mRenderLayer0;
	std::vector<GameObject*>						mRenderLayer1;
	std::vector<GameObject*>						mRenderLayer2;

	std::vector<GameObject*>						mGameObjects;
	std::map<GameObject*, DamageableComponent*>		mDamageableGameObjects;
};