#pragma once

#include "ObjectManager.h"

#include "rapidxml.hpp"

using namespace rapidxml;

class GameLevel
{
public:
	GameLevel();
	~GameLevel();

	void Initalise(GameCamera* cam) { mCamera = cam; }
	void BuildLevel(std::string fileName);

	void Update(float deltaTime);
	void Draw();

private:
	ObjectManager				mObjectManager;

	GameCamera*					mCamera;

	std::vector<GameObject*>	mGameObjects;
};

