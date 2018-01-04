#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd)
{
	GameCamera::Instance().Initalise(wnd);

	LevelBuilder::InitaliseGameplayValues("Levels\\GameValues.xml"); //BROKEN

	mCurrentLevel = 1;
	mWaitingOnGUIInput = false;

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

void Game::UpdateLevel()
{
	float deltaTime = mFrameTimer.Mark();

	GameCamera::Instance().Update(deltaTime);

	mGameLevel->Update(deltaTime);
	mGameGUI->UpdateGUI(deltaTime);

	if (!mWaitingOnGUIInput)
	{
		if (mGameLevel->GetLevelState() == LevelState::eDead)
		{
			mGameGUI->EnableCentreButton("RESTART");
			mWaitingOnGUIInput = true;
		}
		else if (mGameLevel->GetLevelState() == LevelState::eWon)
		{
			mGameGUI->EnableCentreButton("LEVELUP");
			mCurrentLevel++; // Increase level
			mWaitingOnGUIInput = true;
		}
	}
	else
	{
		if (mGameGUI->GetCentreButtonClicked())
		{
			mWaitingOnGUIInput = false;
			CreateLevel();
		}
	}
}

void Game::DrawLevel()
{
	mGameLevel->Draw();
	mGameGUI->DrawGUI();
}