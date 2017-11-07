#include "MainWindow.h"
#include "Game.h"

#include "UpdateDirectionMessage.h"
#include "AddForceMessage.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd)
{
	TransformComponent* dragonTransform = ComponentFactory::MakeTransform(Vec2(50, 75));
	SpriteRendererComponent* dragonSprite = ComponentFactory::MakeSpriteRenderer("Images\\dragon.dds", dragonTransform);
	dragon->AddComponent(dragonTransform);
	dragon->AddComponent(dragonSprite);
	_gameObjects.push_back(dragon);

	TransformComponent* trollTransform = ComponentFactory::MakeTransform(Vec2(200, 75));
	SpriteRendererComponent* trollSprite = ComponentFactory::MakeSpriteRenderer("Images\\troll.dds", trollTransform);
	troll->AddComponent(trollTransform);
	troll->AddComponent(trollSprite);
	_gameObjects.push_back(troll);

	_gameObjects.push_back(player);
}

void Game::Go()
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
		dir.y -= 1.0f;
	}
	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		dir.y += 1.0f;
	}
	if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		dir.x -= 1.0f;
	}
	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		dir.x += 1.0f;
	}

	if (dir.x != 0 || dir.y != 0)
		player->UpdateDir(dir);

	float deltaTime = ft.Mark();

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

	guiText.Draw(gfx);
}
