
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Player.h"
#include "GUIText.h"
#include "FrameTimer.h"

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

	Actor dragon = Actor("Images\\dragon.dds", XMFLOAT2(50, 75));
	Actor troll = Actor("Images\\troll.dds", XMFLOAT2(200, 75));

	Player player = Player("Images\\mage.dds", XMFLOAT2(350, 75));

	GUIText guiText = GUIText("DirectXTK Simple Sample", XMFLOAT2(100, 20));
};