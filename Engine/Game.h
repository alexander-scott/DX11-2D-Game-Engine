
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Surface.h"
#include "FrameTimer.h"
#include "Font.h"
#include "Character.h"

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
	Font font = "Images\\Fixedsys16x28.bmp";
	Character character = Character({ 100.0f,100.0f });
};