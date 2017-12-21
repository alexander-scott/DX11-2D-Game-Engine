#pragma once

#include "ObjectManager.h"
#include "PhysicsManager.h"

#include "rapidxml.hpp"

using namespace rapidxml;

class GameLevel
{
public:
	void Initalise(GameCamera* cam);
	void BuildLevel(std::string fileName);

	void CacheComponents(GameObject* gameObj, int renderLayer);

	void Update(float deltaTime);
	void Draw();

private:
	ObjectManager									mObjectManager;
	PhysicsManager									mPhysicsManager;
	LevelData										mLevelData;

	GameCamera*										mCamera;

	std::vector<GameObject*>						mRenderLayer0;
	std::vector<GameObject*>						mRenderLayer1;
	std::vector<GameObject*>						mRenderLayer2;

	std::vector<GameObject*>						mGameObjects;
	std::map<GameObject*, DamageableComponent*>		mDamageableGameObjects;
};

