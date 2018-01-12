#pragma once

#include "FrameTimer.h"
#include "MainWindow.h"

#include "LevelBuilder.h"
#include "GameGUI.h"
#include "GameStartScreen.h"

using namespace std;

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

	void UpdateStartScreen();

	MainWindow& wnd;

	FrameTimer							mFrameTimer;

	shared_ptr<GameLevel>				mGameLevel;

	unique_ptr<GameStartScreen>			mGameStartScreen;
	unique_ptr<GameGUI>					mGameGUI;

	int									mCurrentLevel;
	float								mTotalScore;
	GameState							mGameState;
};