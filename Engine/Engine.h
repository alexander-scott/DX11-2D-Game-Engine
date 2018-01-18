#pragma once

#include "FrameTimer.h"
#include "MainWindow.h"

#include "LevelBuilder.h"
#include "ScenePersistentValues.h"

using namespace std;

class Engine
{
public:
	Engine(class MainWindow& wnd, int width, int height, std::string resourcesPath);
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

	void Update();

	~Engine();

	MainWindow& wnd;

private:
	void CreateLevel();

	void DrawLevel();
	void UpdateLevel();

	FrameTimer							mFrameTimer;

	shared_ptr<GameLevel>				mGameLevel;
};