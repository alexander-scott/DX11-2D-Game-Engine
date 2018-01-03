#pragma once

#include "ObjectManager.h"
#include "PhysicsManager.h"

class GameLevel
{
public:
	GameLevel();
	~GameLevel();

	void CacheComponents(GameObject* gameObj, int renderLayer);
	void ConstructLevel(LevelData levelData);

	void Update(float deltaTime);
	void Draw();

private:
	ObjectManager									mObjectManager;
	PhysicsManager									mPhysicsManager;
	LevelData										mLevelData;

	GameObject*										mText;

	std::vector<GameObject*>						mRenderLayer0;
	std::vector<GameObject*>						mRenderLayer1;
	std::vector<GameObject*>						mRenderLayer2;

	std::vector<GameObject*>						mGameObjects;
	std::map<GameObject*, DamageableComponent*>		mDamageableGameObjects;
};