
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "GUIText.h"
#include "FrameTimer.h"
#include "ComponentFactory.h"
#include "GameObject.h"

class Game
{
public:
	Game(class MainWindow& wnd);
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	void Go();

private:
	void ComposeFrame();
	void UpdateModel();

private:
	MainWindow& wnd;
	Graphics gfx;

	FrameTimer ft;

	GameObject* dragon = new GameObject();
	GameObject* troll = new GameObject();

	GameObject* player = new GameObject();

	GUIText guiText = GUIText("DirectXTK Simple Sample", XMFLOAT2(100, 20));
};