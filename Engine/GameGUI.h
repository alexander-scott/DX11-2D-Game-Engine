#pragma once

#include "GameLevel.h"

class GameGUI
{
public:
	GameGUI(GameLevel* gameLevel);
	~GameGUI();

	void UpdateGUI(float deltaTime);
	void DrawGUI();

private:
	GameLevel*										mGameLevel;
	std::vector<GameObject*>						mGameObjects;
	float											mTotalScore;
};

