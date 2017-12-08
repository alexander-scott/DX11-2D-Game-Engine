#pragma once

#include "FrameTimer.h"
#include "MainWindow.h"

#include "ComponentFactory.h"
#include "PhysicsManager.h"

#include "GameCamera.h"
#include "Player.h"
#include "Ball.h"
#include "GameLevelManager.h"

class Game
{
public:
	Game(class MainWindow& wnd);
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	void Update();

	~Game();

private:
	void InitaliseLevel();
	void InitaliseBackground(LevelData& levelData);
	void InitaliseObjects(LevelData& levelData);
	void InitaliseGUI();

	void InitalisePhysics();

	void ComposeFrame();
	void UpdateModel();

private:
	MainWindow& wnd;

	GameCamera*						_camera;
	Player*							_player;

	FrameTimer						_frameTimer;
	PhysicsManager					_physicsManager;
	std::vector<GameObject*>		_gameObjects;
};