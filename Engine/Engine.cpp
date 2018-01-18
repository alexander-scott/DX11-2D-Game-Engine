#include "Engine.h"

Engine::Engine(MainWindow& wnd, int width, int height, std::string resourcesPath)
	:
	wnd(wnd)
{
	ApplicationValues::Instance().ScreenWidth = width;
	ApplicationValues::Instance().ScreenHeight = height;
	ApplicationValues::Instance().ResourcesPath = resourcesPath;

	Camera::Instance().Initalise(wnd, new DX11Graphics());
	Audio::Instance().CreateSoundEffects(ApplicationValues::Instance().ResourcesPath);

	LevelBuilder::InitaliseGameplayValues(ApplicationValues::Instance().ResourcesPath + "\\Levels\\Prefabs.xml"); //BROKEN

	ScenePersistentValues::Instance().Values["CurrentLevel"].reset(new PersistentValue<float>(1));
	ScenePersistentValues::Instance().Values["TotalScore"].reset(new PersistentValue<float>(0));

	mGameState = GameState::ePlayingGame;
	CreateLevel();
}


void Engine::Update()
{
	Camera::Instance().BeginFrame();

	// If game is playing
	UpdateLevel();
	DrawLevel();

	Camera::Instance().EndFrame();

	Audio::Instance().Update();
}

Engine::~Engine()
{
	mGameLevel = nullptr;
}

void Engine::CreateLevel()
{
	// Delete old level
	if (ScenePersistentValues::Instance().GetValue<float>("CurrentLevel") != 1) // HARDCODED 
	{
		float totalScore = ScenePersistentValues::Instance().GetValue<float>("TotalScore");
		totalScore += mGameLevel->GetScore();
		ScenePersistentValues::Instance().Values["TotalScore"].reset(new PersistentValue<float>(totalScore));

		mGameLevel = nullptr;
	}
		
	stringstream stream;
	//stream << ApplicationValues::Instance().ResourcesPath + "\\Levels\\Level" << ScenePersistentValues::Instance().GetValue<float>("CurrentLevel") << ".xml";
	stream << ApplicationValues::Instance().ResourcesPath + "\\Levels\\Scene.xml";
	string levelPath = stream.str();

	mGameLevel = LevelBuilder::BuildGameLevel(levelPath, ScenePersistentValues::Instance().GetValue<float>("TotalScore"));
}

void Engine::CheckLevelOver()
{
	if (mGameState != GameState::eWaitingOnGUIInput)
	{
		if (mGameLevel->GetLevelState() == LevelState::eDead)
		{
			//mGameGUI->EnableCentreButton("RESTART");
			mGameState = GameState::eWaitingOnGUIInput;
		}
		else if (mGameLevel->GetLevelState() == LevelState::eWon)
		{
			//mGameGUI->EnableCentreButton("LEVELUP");

			float currentLevel = ScenePersistentValues::Instance().GetValue<float>("CurrentLevel");
			currentLevel++; // Increase level
			ScenePersistentValues::Instance().Values["CurrentLevel"].reset(new PersistentValue<float>(currentLevel));

			mGameState = GameState::eWaitingOnGUIInput;
		}
	}
	else
	{
		//if (mGameGUI->GetCentreButtonClicked())
		if (false)
		{
			mGameState = GameState::ePlayingGame;
			CreateLevel();
		}
	}
}

void Engine::UpdateLevel()
{
	float deltaTime = mFrameTimer.Mark();

	Camera::Instance().Update(deltaTime);

	mGameLevel->Update(deltaTime);

	CheckLevelOver();
}

void Engine::DrawLevel()
{
	mGameLevel->Draw();
}