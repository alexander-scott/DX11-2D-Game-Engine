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

	LoadScene("Scene1");
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
	mScene = nullptr;
}

void Engine::UpdateScene()
{
	float deltaTime = mFrameTimer.Mark();

	Camera::Instance().Update(deltaTime);

	if (SceneManagement::Instance().LoadNewScene)
	{
		LoadScene(SceneManagement::Instance().NewSceneName);
	}

	mScene->Update(deltaTime);
}

void Engine::DrawScene()
{
	mScene->Draw();
}

void Engine::LoadScene(std::string sceneName)
{
	mScene = nullptr;
	SceneManagement::Instance().LoadNewScene = false;

	stringstream stream;
	stream << ApplicationValues::Instance().ResourcesPath + "\\Levels\\" + sceneName + ".xml";
	string scenePath = stream.str();

	mScene = make_shared<Scene>();
	SceneBuilder::BuildScene(mScene, scenePath);
}