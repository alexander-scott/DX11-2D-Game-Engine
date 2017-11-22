#include "Game.h"

#include "AddForceMessage.h"

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
	// process key messages while any remain
	while (!wnd.kbd.KeyIsEmpty())
	{
		const auto e = wnd.kbd.ReadKey();
	}

	Vec2 dir = Vec2(0.0f,0.0f);
	/*if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		dir.y += 0.00001f;
	}
	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		dir.y -= 0.00001f;
	}*/
	if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		dir.x += 0.00001f;
	}
	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		dir.x -= 0.00001f;
	}

	// Move the player in the specified direction
	if (dir.x != 0 || dir.y != 0)
	{
		AddForceMessage addForceMsg("Add Force");
		addForceMsg.SetForce(dir);
		player->SendMessageToComponents(addForceMsg);
	}

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
