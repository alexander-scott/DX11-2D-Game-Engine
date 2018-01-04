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

	bool GetCentreButtonClicked() { return mCentreButtonClicked; }

private:
	void BuildStartScreen();

	std::vector<GameObject*>				mGameObjects;
	GUIButtonComponent*						mCentreButton;
	bool									mCentreButtonClicked;
};