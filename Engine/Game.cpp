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

	//player.Init("Images\\mage_walk.dds", XMFLOAT2(350, 75), 0);
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

	//player.UpdateDirection(dir);
	//player.Update(ft.Mark());

	troll->Update(ft.Mark());
	dragon->Update(ft.Mark());
}

void Game::ComposeFrame()
{
	/*dragon.Draw(gfx);
	troll.Draw(gfx);

	player.Draw(gfx);*/

	troll->Draw(gfx);
	dragon->Draw(gfx);

	guiText.Draw(gfx);
}
