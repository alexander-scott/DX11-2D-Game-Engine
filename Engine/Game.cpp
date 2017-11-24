#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd)
{
	InitaliseObjects();
	InitalisePhysics();
}

void Game::InitaliseObjects()
{
	int startX = 50;
	int y = 300;
	int step = 50;
	for (int i = 0; i < 15; i++)
	{
		_gameObjects.push_back(new WorldTile("Images\\warp_pipe_edited.dds", Vec2(startX + (i * 45), y)));
	}

	for (int i = 0; i < 15; i++)
	{
		_gameObjects.push_back(new WorldTile("Images\\warp_pipe_edited.dds", Vec2(startX + (i * 45), y - 200)));
	}

	_gameObjects.push_back(new WorldTile("Images\\warp_pipe_edited.dds", Vec2(200, 200)));
	
	TransformComponent* guiTextTransform = ComponentFactory::MakeTransform(Vec2(100, 20), 0, 1);
	TextRendererComponent* guiTextRenderer = ComponentFactory::MakeTextRenderer("DirectXTK Simple Sample", guiTextTransform);
	GameObject* guiText = new GameObject();
	guiText->AddComponent(guiTextTransform);
	guiText->AddComponent(guiTextRenderer);
	_gameObjects.push_back(guiText);

	player = new Player();
	_gameObjects.push_back(player);
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
