#include "MainWindow.h"
#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd)
{
	TransformComponent* dragonTransform = ComponentFactory::MakeTransform(Vec2(50, 75));
	SpriteRendererComponent* dragonSprite = ComponentFactory::MakeSpriteRenderer("Images\\dragon.dds", dragonTransform);
	dragon->AddComponent(dragonTransform);
	dragon->AddComponent(dragonSprite);

	TransformComponent* trollTransform = ComponentFactory::MakeTransform(Vec2(200, 75));
	SpriteRendererComponent* trollSprite = ComponentFactory::MakeSpriteRenderer("Images\\troll.dds", trollTransform);
	troll->AddComponent(trollTransform);
	troll->AddComponent(trollSprite);

	TransformComponent* playerTransform = ComponentFactory::MakeTransform(Vec2(350, 75));
	SpriteAnimatorComponent* playerAnimator = ComponentFactory::MakeSpriteAnimator("Images\\mage_walk.dds", playerTransform);
	player->AddComponent(playerTransform);
	player->AddComponent(playerAnimator);
}

void Game::Go()
{
	gfx.BeginFrame();

	UpdateModel();
	ComposeFrame();

	gfx.EndFrame();
}

void Game::UpdateModel()
{
	// process key messages while any remain
	while (!wnd.kbd.KeyIsEmpty())
	{
		const auto e = wnd.kbd.ReadKey();
	}

	XMFLOAT2 dir = XMFLOAT2(0.0f,0.0f);
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

	float deltaTime = ft.Mark();

	troll->Update(deltaTime);
	dragon->Update(deltaTime);

	player->Update(deltaTime);
}

void Game::ComposeFrame()
{
	troll->Draw(gfx);
	dragon->Draw(gfx);
	player->Draw(gfx);

	guiText.Draw(gfx);
}
