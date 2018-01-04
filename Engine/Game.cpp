#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd)
{
	GameCamera::Instance().Initalise(wnd);

	LevelBuilder::InitaliseGameplayValues("Levels\\GameValues.xml"); //BROKEN

	mCurrentLevel = 1;
	mGameState = GameState::ePlayingGame;

	mGameGUI = new GameGUI();

	CreateLevel();
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

void Game::CreateLevel()
{
	// Delete old level
	if (mCurrentLevel != 1) // HARDCODED 
		delete mGameLevel;

	std::stringstream stream;
	stream << "Levels\\Level" << mCurrentLevel << ".xml";
	string levelPath = stream.str();

	mGameLevel = LevelBuilder::BuildGameLevel(levelPath);
	mGameGUI->ResetGUI(mGameLevel, mCurrentLevel);
}

void Game::CheckLevelOver()
{
	if (mGameState != GameState::eWaitingOnGUIInput)
	{
		if (mGameLevel->GetLevelState() == LevelState::eDead)
		{
			mGameGUI->EnableCentreButton("RESTART");
			mGameState = GameState::eWaitingOnGUIInput;
		}
		else if (mGameLevel->GetLevelState() == LevelState::eWon)
		{
			mGameGUI->EnableCentreButton("LEVELUP");
			mCurrentLevel++; // Increase level
			mGameState = GameState::eWaitingOnGUIInput;
		}
	}
	else
	{
		if (mGameGUI->GetCentreButtonClicked())
		{
			mGameState = GameState::ePlayingGame;
			CreateLevel();
		}
	}
}

void Game::UpdateLevel()
{
	float deltaTime = mFrameTimer.Mark();

	GameCamera::Instance().Update(deltaTime);

	mGameLevel->Update(deltaTime);
	mGameGUI->UpdateGUI(deltaTime);

	CheckLevelOver();
}

void Game::DrawLevel()
{
	mGameLevel->Draw();
	mGameGUI->DrawGUI();
}