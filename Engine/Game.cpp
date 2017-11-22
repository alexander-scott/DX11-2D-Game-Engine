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
	TransformComponent* pipeTransform = ComponentFactory::MakeTransform(Vec2(350, 250), 0, 0.3);
	SpriteRendererComponent* pipeSprite = ComponentFactory::MakeSpriteRenderer("Images\\warp_pipe_edited.dds", pipeTransform);
	RigidBodyComponent* pipeRigidbody = ComponentFactory::MakeRigidbody(true);

	// 0,0 is TOP LEFT CORNER
	Vec2 *vertices = new Vec2[4];
	vertices[0].Set(10, 10);
	vertices[1].Set(-20, 10);
	vertices[2].Set(10, -30);
	vertices[3].Set(-20, -30);

	PolygonColliderComponent * pipeCollider = ComponentFactory::MakePolygonCollider(vertices, 4, pipeTransform, pipeRigidbody);

	GameObject* pipeObj = new GameObject();
	pipeObj->AddComponent(pipeTransform);
	pipeObj->AddComponent(pipeSprite);
	pipeObj->AddComponent(pipeRigidbody);
	pipeObj->AddComponent(pipeCollider);
	_gameObjects.push_back(pipeObj);

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
	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		dir.y += 0.000001f;
	}
	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		dir.y -= 0.000001f;
	}
	if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		dir.x += 0.000001f;
	}
	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		dir.x -= 0.000001f;
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
