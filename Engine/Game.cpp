#include "MainWindow.h"
#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd)
{
	Vei2 v;
	auto v2 = v.GetNormalized();
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
}

void Game::ComposeFrame()
{
	font.DrawText("Test\nText", wnd.mouse.GetPos() - Vei2{ 50,100 }, Colors::White, gfx);
}
