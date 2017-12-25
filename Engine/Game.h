#pragma once

#include "FrameTimer.h"
#include "MainWindow.h"

#include "GameLevel.h"
#include "GameCamera.h"

class Game
{
public:
	Game(class MainWindow& wnd);
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	void Update();

	~Game();

private:
	void ComposeFrame();
	void UpdateLevel();

private:
	MainWindow& wnd;

	GameLevel*									mGameLevel;

	FrameTimer									mFrameTimer;
};