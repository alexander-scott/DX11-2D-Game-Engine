#pragma once

#include "FrameTimer.h"
#include "MainWindow.h"

#include "LevelBuilder.h"
#include "GameGUI.h"

#include <sstream>

class Game
{
public:
	Game(class MainWindow& wnd);
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	void Update();

	~Game();

private:
	void CreateLevel();
	void CheckLevelOver();

	void DrawLevel();
	void UpdateLevel();

	MainWindow& wnd;

	FrameTimer					mFrameTimer;

	GameLevel*					mGameLevel;
	GameGUI*					mGameGUI;

	int							mCurrentLevel;
	bool						mWaitingOnGUIInput;
};