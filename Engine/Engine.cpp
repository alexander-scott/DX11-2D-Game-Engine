#include "Engine.h"

Engine::Engine(MainWindow& wnd, int width, int height, std::string resourcesPath)
	: wnd(wnd)
{
	ApplicationValues::Instance().ScreenWidth = width;
	ApplicationValues::Instance().ScreenHeight = height;
	ApplicationValues::Instance().ResourcesPath = resourcesPath;

	Camera::Instance().Initalise(wnd, new DX11Graphics());
	Audio::Instance().CreateSoundEffects(ApplicationValues::Instance().ResourcesPath);

	SceneBuilder::InitaliseGameplayValues(ApplicationValues::Instance().ResourcesPath + "\\Levels\\Prefabs.xml"); //BROKEN

	ScenePersistentValues::Instance().Values["CurrentLevel"].reset(new PersistentValue<float>(1));
	ScenePersistentValues::Instance().Values["TotalScore"].reset(new PersistentValue<float>(0));

	mSceneManager.LoadScene("Scene1");
}

void Engine::Update()
{
	Camera::Instance().BeginFrame();

	// If game is playing
	UpdateScene();
	DrawScene();

	Camera::Instance().EndFrame();

	Audio::Instance().Update();
}

Engine::~Engine()
{
	
}

void Engine::UpdateScene()
{
	float deltaTime = mFrameTimer.Mark();

	Camera::Instance().Update(deltaTime);

	if (ISceneManager::Instance().LoadNewScene)
	{
		ISceneManager::Instance().LoadNewScene = false;
		mSceneManager.LoadScene(ISceneManager::Instance().NewSceneName);
	}

	mSceneManager.Update(deltaTime);
}

void Engine::DrawScene()
{
	mSceneManager.Draw();
}