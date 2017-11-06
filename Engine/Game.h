
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Player.h"
#include "GUIText.h"
#include "FrameTimer.h"
#include "ComponentFactory.h"

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

	//Player player;

	GUIText guiText = GUIText("DirectXTK Simple Sample", XMFLOAT2(100, 20));
};