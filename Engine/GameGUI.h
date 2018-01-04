#pragma once

#include "GameLevel.h"

class GameGUI
{
public:
	GameGUI();
	~GameGUI();

	void UpdateGUI(float deltaTime);
	void DrawGUI();

	void ResetGUI(GameLevel* gameLevel, int currentLevel);

	void EnableCentreButton(std::string buttonText);

	bool GetCentreButtonClicked() {	return mCentreButtonClicked; }

private:
	void BuildGUI();
	GameObject* FindGameObject(std::string tag);

	std::vector<GameObject*>				mGameObjects;
	float									mTotalScore;
	
	GUIButtonComponent*						mCentreButton;

	bool									mCentreButtonClicked;
};

