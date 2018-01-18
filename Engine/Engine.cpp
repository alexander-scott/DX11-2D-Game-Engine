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
	mGameLevel = nullptr;
		
	stringstream stream;
	//stream << ApplicationValues::Instance().ResourcesPath + "\\Levels\\Level" << ScenePersistentValues::Instance().GetValue<float>("CurrentLevel") << ".xml";
	stream << ApplicationValues::Instance().ResourcesPath + "\\Levels\\Scene.xml";
	string levelPath = stream.str();

	mGameLevel = LevelBuilder::BuildGameLevel(levelPath, ScenePersistentValues::Instance().GetValue<float>("TotalScore"));
}

void Engine::UpdateLevel()
{
	float deltaTime = mFrameTimer.Mark();

	Camera::Instance().Update(deltaTime);

	mGameLevel->Update(deltaTime);
}

void Engine::DrawLevel()
{
	mGameLevel->Draw();
}