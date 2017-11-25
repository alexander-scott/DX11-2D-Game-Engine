#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd)
{
	gfx.PreloadTextures();

	InitaliseObjects();
	InitalisePhysics();
}

void Game::InitaliseObjects()
{
	/*float startX = 50;
	float y = 300;
	float step = 50;

	for (float i = 0; i < 15; i++)
	{
		_gameObjects.push_back(new WorldTile("Pipe", Vec2(startX + (i * 45), y)));
	}

	for (float i = 0; i < 15; i++)
	{
		_gameObjects.push_back(new WorldTile("Pipe", Vec2(startX + (i * 45), y - 200)));
	}

	_gameObjects.push_back(new WorldTile("Pipe", Vec2(200, 200)));*/

	LevelManager levelManager(45, 45, 0, 200);
	levelManager.LoadLevel("Levels\\level1.xml");
	for (int i = 0; i < levelManager.GetWidth(); i++)
	{
		for (int j = 0; j < levelManager.GetHeight(); j++)
		{
			WorldTile* t = levelManager.GetTile(i, j);
			if (t != nullptr)
			{
				_gameObjects.push_back(t);
			}
		}
	}
	
	TransformComponent* guiTextTransform = ComponentFactory::MakeTransform(Vec2(100, 20), 0, 1);
	TextRendererComponent* guiTextRenderer = ComponentFactory::MakeTextRenderer("DirectXTK Simple Sample", guiTextTransform);
	GameObject* guiText = new GameObject();
	guiText->AddComponent(guiTextTransform);
	guiText->AddComponent(guiTextRenderer);
	_gameObjects.push_back(guiText);

	_gameObjects.push_back(new Player());
}

void Game::InitalisePhysics()
{
	// TODO: PHYSICSSS
	// Add all gameobjects which have colliders to a physics manager which will then check for collisions every frame.
	for (auto go : _gameObjects)
	{
		ColliderComponent* goCollider = go->GetComponent<ColliderComponent>();

		if (goCollider != nullptr)
		{
			physicsManager.AddCollider(goCollider);
		}
	}
}

void Game::Update()
{
	gfx.BeginFrame();

	UpdateModel();
	ComposeFrame();

	gfx.EndFrame();
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
	float deltaTime = ft.Mark();

	physicsManager.Update(deltaTime);

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
		go->Draw(gfx);
	}
}
