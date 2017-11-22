
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "GUIText.h"
#include "FrameTimer.h"
#include "ComponentFactory.h"
#include "GameObject.h"
#include "MainWindow.h"
#include "PhysicsManager.h"

#include "Player.h"
#include "WorldTile.h"

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
	void InitalisePhysics();

	void ComposeFrame();
	void UpdateModel();

private:
	MainWindow& wnd;
	Graphics gfx;
	FrameTimer ft;

	PhysicsManager physicsManager;

	std::vector<GameObject*> _gameObjects;

	Player* player;
};