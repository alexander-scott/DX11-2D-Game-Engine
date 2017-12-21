#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd)
{
	mCamera = new GameCamera("Camera");
	mCamera->Initalise(wnd);

	mGameLevel = new GameLevel(mCamera);
	mGameLevel->BuildLevel("Levels\\Level1.xml");
}

void Game::Update()
{
	mCamera->BeginFrame();

	UpdateLevel();
	ComposeFrame();

	mCamera->EndFrame();

	Audio::Instance().Update();
}

Game::~Game()
{
	delete mGameLevel;
}

void Game::UpdateLevel()
{
	float deltaTime = mFrameTimer.Mark();

	mGameLevel->Update(deltaTime);
}

void Game::ComposeFrame()
{
	mGameLevel->Draw();
}