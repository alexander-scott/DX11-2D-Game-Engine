#include "Engine.h"

Engine::Engine(MainWindow& wnd, int width, int height, std::string resourcesPath)
	:
	wnd(wnd)
{
	ApplicationValues::Instance().ScreenWidth = width;
	ApplicationValues::Instance().ScreenHeight = height;
	ApplicationValues::Instance().ResourcesPath = resourcesPath;

	GameCamera::Instance().Initalise(wnd);
	Audio::Instance().CreateSoundEffects(ApplicationValues::Instance().ResourcesPath);

	LevelBuilder::InitaliseGameplayValues(ApplicationValues::Instance().ResourcesPath + "\\Levels\\Prefabs.xml"); //BROKEN

	ScenePersistentValues::Instance().Values["CurrentLevel"].reset(new PersistentValue<int>(1));
	ScenePersistentValues::Instance().Values["TotalScore"].reset(new PersistentValue<float>(0));

	mGameState = GameState::ePlayingGame;
	mGameGUI = make_unique<GameGUI>();
	CreateLevel();
}


void Engine::Update()
{
	GameCamera::Instance().BeginFrame();

	// If game is playing
	UpdateLevel();
	DrawLevel();

	GameCamera::Instance().EndFrame();

	Audio::Instance().Update();
}

Engine::~Engine()
{
	mGameLevel = nullptr;
}

void Engine::CreateLevel()
{
	// Delete old level
	if (ScenePersistentValues::Instance().GetValue<int>("CurrentLevel") != 1) // HARDCODED 
	{
		float totalScore = ScenePersistentValues::Instance().GetValue<float>("TotalScore");
		totalScore += mGameLevel->GetScore();
		ScenePersistentValues::Instance().Values["TotalScore"].reset(new PersistentValue<float>(totalScore));

		mGameLevel = nullptr;
	}
		
	stringstream stream;
	stream << ApplicationValues::Instance().ResourcesPath + "\\Levels\\Level" << ScenePersistentValues::Instance().GetValue<int>("CurrentLevel") << ".xml";
	string levelPath = stream.str();

	mGameLevel = LevelBuilder::BuildGameLevel(levelPath, ScenePersistentValues::Instance().GetValue<float>("TotalScore"));
	mGameGUI->ResetGUI(mGameLevel, ScenePersistentValues::Instance().GetValue<int>("CurrentLevel"));
}

void Engine::CheckLevelOver()
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

			int currentLevel = ScenePersistentValues::Instance().GetValue<int>("CurrentLevel");
			currentLevel++; // Increase level
			ScenePersistentValues::Instance().Values["CurrentLevel"].reset(new PersistentValue<int>(currentLevel));

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

void Engine::UpdateLevel()
{
	float deltaTime = mFrameTimer.Mark();

	GameCamera::Instance().Update(deltaTime);

	mGameLevel->Update(deltaTime);
	mGameGUI->UpdateGUI(deltaTime);

	CheckLevelOver();
}

void Engine::DrawLevel()
{
	mGameLevel->Draw();
	mGameGUI->DrawGUI();
}