#pragma once

#include "GameObject.h"
#include "GameComponentFactory.h"
#include "GameCamera.h"

class GameStartScreen
{
public:
	GameStartScreen();
	~GameStartScreen();

	void UpdateGUI(float deltaTime);
	void DrawGUI();

	void BuildStartScreen();

	bool GetCentreButtonClicked() { return mCentreButtonClicked; }

private:
	std::vector<GameObject*>				mGameObjects;
	GUIButtonComponent*						mCentreButton;
	bool									mCentreButtonClicked;
};