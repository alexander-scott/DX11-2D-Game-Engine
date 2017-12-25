#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd)
{
	mCamera = new GameCamera("Camera");
	mCamera->Initalise(wnd);

	//ObjectManager::InitaliseGameplayValues("Levels\\GameValues.xml"); //BROKEN

	mGameLevel = new GameLevel(mCamera, "Levels\\Level1.xml");
	mGameLevel->BuildLevel();
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