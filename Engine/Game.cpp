#include "MainWindow.h"
#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd)
{
	dragon.Init("Images\\dragon.dds", XMFLOAT2(50, 75));
	troll.Init("Images\\troll.dds", XMFLOAT2(200, 75));

	player.Init("Images\\mage.dds", XMFLOAT2(350, 75));
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

	player.UpdateDirection(dir);
	player.Update(ft.Mark());
}

void Game::ComposeFrame()
{
	dragon.Draw(gfx);
	troll.Draw(gfx);

	player.Draw(gfx);

	guiText.Draw(gfx);
}
