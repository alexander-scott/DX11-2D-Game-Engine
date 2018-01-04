#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd)
{
	GameCamera::Instance().Initalise(wnd);

	LevelBuilder::InitaliseGameplayValues("Levels\\GameValues.xml"); //BROKEN

	mGameLevel = LevelBuilder::BuildGameLevel("Levels\\Level1.xml");
	mGameGUI = new GameGUI(mGameLevel);
}

void Game::Update()
{
	GameCamera::Instance().BeginFrame();

	UpdateLevel();
	DrawLevel();

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

	GameCamera::Instance().Update(deltaTime);
	mGameLevel->Update(deltaTime);
	mGameGUI->UpdateGUI(deltaTime);
}

void Game::DrawLevel()
{
	mGameLevel->Draw();
	mGameGUI->DrawGUI();
}