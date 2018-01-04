#pragma once

#include "GameLevel.h"

class GameGUI
{
public:
	GameGUI(GameLevel* gameLevel);
	~GameGUI();

	void UpdateGUI(float deltaTime);
	void DrawGUI();

	void EnableCentreButton(std::string buttonText);

	bool GetCentreButtonClicked() {	return mCentreButtonClicked; }

private:
	void BuildGUI();

	GameLevel*								mGameLevel;
	std::vector<GameObject*>				mGameObjects;
	float									mTotalScore;
	
	GameObject*								mCentreButtonSprite;
	GameObject*								mCentreButtonText;
	GUIButtonComponent*						mCentreButton;

	bool									mCentreButtonClicked;
};

