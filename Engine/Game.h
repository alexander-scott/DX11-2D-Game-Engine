
#pragma once

#include "Graphics.h"
#include "GUIText.h"
#include "FrameTimer.h"
#include "ComponentFactory.h"
#include "GameObject.h"
#include "MainWindow.h"
#include "PhysicsManager.h"

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
	Graphics gfx;

	FrameTimer						_frameTimer;
	PhysicsManager					_physicsManager;
	std::vector<GameObject*>		_gameObjects;
};