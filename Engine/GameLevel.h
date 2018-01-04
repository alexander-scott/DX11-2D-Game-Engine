#pragma once

#include "ObjectManager.h"
#include "PhysicsManager.h"

class GameLevel
{
public:
	GameLevel(float startScore);
	~GameLevel();

	void Update(float deltaTime);
	void Draw();

	LevelState GetLevelState() { return mLevelState; }
	float& GetScore() { return mScore; }

	void CacheComponents(GameObject* gameObj, int renderLayer);

	void ConstructLevel(LevelData levelData);
	void ConstructionComplete();

	GameObject* FindGameObject(std::string tag);

private:
	void SetupCamera();
	void RegisterFinishFlag();

	PhysicsManager									mPhysicsManager;
	LevelData										mLevelData;

	LevelState										mLevelState;
	TriggerBoxComponent*							mFinishFlagTrigger;

	std::vector<GameObject*>						mRenderLayer0;
	std::vector<GameObject*>						mRenderLayer1;
	std::vector<GameObject*>						mRenderLayer2;

	std::vector<GameObject*>						mGameObjects;
	std::map<GameObject*, DamageableComponent*>		mDamageableGameObjects;

	float											mScore;
};