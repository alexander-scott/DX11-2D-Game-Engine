#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd)
{
	GameCamera::Instance().Initalise(wnd);

	LevelBuilder::InitaliseGameplayValues("Levels\\GameValues.xml"); //BROKEN

	mGameLevel = LevelBuilder::BuildGameLevel("Levels\\Level1.xml");
}

void Game::Update()
{
	GameCamera::Instance().BeginFrame();

	UpdateLevel();
	ComposeFrame();

	GameCamera::Instance().EndFrame();

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