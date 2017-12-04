#pragma once

#include "FrameTimer.h"
#include "MainWindow.h"

#include "ComponentFactory.h"
#include "PhysicsManager.h"

#include "GameCamera.h"
#include "Player.h"
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
	void InitaliseObjects();
	void InitaliseLevel();

	void InitalisePhysics();

	void ComposeFrame();
	void UpdateModel();

private:
	MainWindow& wnd;

	GameCamera*						_camera;

	FrameTimer						_frameTimer;
	PhysicsManager					_physicsManager;
	std::vector<GameObject*>		_gameObjects;
};