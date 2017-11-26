
#pragma once

#include "DX11Graphics.h"

#include "FrameTimer.h"
#include "ComponentFactory.h"
#include "GameObject.h"
#include "MainWindow.h"
#include "PhysicsManager.h"

#include "Camera.h"
#include "Player.h"
#include "LevelManager.h"

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

	Camera*							_camera;

	FrameTimer						_frameTimer;
	PhysicsManager					_physicsManager;
	std::vector<GameObject*>		_gameObjects;
};