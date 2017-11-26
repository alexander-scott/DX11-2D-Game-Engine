#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd)
{
	_camera = new GameCamera();
	_camera->Initalise(wnd);

	InitaliseObjects();
	InitaliseLevel();
	InitalisePhysics();
}

// Create any custom objects such as player
void Game::InitaliseObjects()
{
	TransformComponent* guiTextTransform = ComponentFactory::MakeTransform(Vec2(100, 20), 0, 1);
	TextRendererComponent* guiTextRenderer = ComponentFactory::MakeTextRenderer("DirectXTK Simple Sample", guiTextTransform);
	GameObject* guiText = new GameObject();
	guiText->AddComponent(guiTextTransform);
	guiText->AddComponent(guiTextRenderer);
	_gameObjects.push_back(guiText);

	_gameObjects.push_back(_camera);
}

// Read in level data from an XML file and build the level
void Game::InitaliseLevel()
{
	LevelManager levelManager(45, 45, 0, 600);
	levelManager.LoadLevel("Levels\\level1.xml");

	Player* p = new Player(levelManager.GetLevelData().playerXPos, levelManager.GetLevelData().playerYPos);
	_gameObjects.push_back(p);
	_camera->SetFocusTrans(p->GetComponent<TransformComponent>()); // First object is the player

	for (int i = 0; i < levelManager.GetLevelData().levelWidth; i++)
	{
		for (int j = 0; j < levelManager.GetLevelData().levelHeight; j++)
		{
			WorldTile* t = levelManager.GetTile(i, j);
			if (t != nullptr)
			{
				_gameObjects.push_back(t);
			}
		}
	}
}

// Add all gameobjects which have colliders to a physics manager which will then check for collisions every frame.
void Game::InitalisePhysics()
{
	for (auto go : _gameObjects)
	{
		ColliderComponent* goCollider = go->GetComponent<ColliderComponent>();

		if (goCollider != nullptr)
		{
			_physicsManager.AddCollider(goCollider);
		}
	}
}

void Game::Update()
{
	_camera->BeginFrame();

	UpdateModel();
	ComposeFrame();

	_camera->EndFrame();
}

Game::~Game()
{
	for (auto go : _gameObjects)
	{
		go->~GameObject();
	}
}

void Game::UpdateModel()
{
	float deltaTime = _frameTimer.Mark();

	_physicsManager.Update(deltaTime);

	// Update gameobjects
	for (auto go : _gameObjects)
	{
		go->Update(deltaTime);
	}
}

void Game::ComposeFrame()
{
	for (auto go : _gameObjects)
	{
		go->Draw(_camera);
	}
}
