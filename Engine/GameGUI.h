#pragma once

#include "GameLevel.h"

class GameGUI
{
public:
	GameGUI();
	~GameGUI();

	void UpdateGUI(float deltaTime);
	void DrawGUI();

	void EnableCentreButton(std::string buttonText);

	bool GetCentreButtonClicked() {	return mCentreButtonClicked; }

private:
	shared_ptr<GameObject> FindGameObject(std::string tag);

	std::vector<shared_ptr<GameObject>>		mGameObjects;
	float									mTotalScore;
	
	GUIButtonComponent*						mCentreButton;

	bool									mCentreButtonClicked;
};