#pragma once

#include "FrameTimer.h"
#include "MainWindow.h"

#include "LevelBuilder.h"
#include "GameGUI.h"

class Game
{
public:
	Game(class MainWindow& wnd);
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	void Update();

	~Game();

private:
	void DrawLevel();
	void UpdateLevel();

private:
	MainWindow& wnd;

	FrameTimer					mFrameTimer;

	GameLevel*					mGameLevel;
	GameGUI*					mGameGUI;

	int							mCurrentLevel;
};