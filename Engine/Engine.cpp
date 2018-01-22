#include "Engine.h"

Engine::Engine(MainWindow& wnd, int width, int height, std::string resourcesPath)
	: wnd(wnd)
{
	ApplicationValues::Instance().ScreenWidth = width;
	ApplicationValues::Instance().ScreenHeight = height;
	ApplicationValues::Instance().ResourcesPath = resourcesPath;

	mGraphics = new DX11Graphics();
	mGraphics->Initalise(wnd);
	mGraphics->PreloadTextures();

	Audio::Instance().CreateSoundEffects(ApplicationValues::Instance().ResourcesPath);

	SceneBuilder::InitaliseGameplayValues(ApplicationValues::Instance().ResourcesPath + "\\Levels\\Prefabs.xml"); //BROKEN

	ScenePersistentValues::Instance().Values["CurrentLevel"].reset(new PersistentValue<float>(1));
	ScenePersistentValues::Instance().Values["TotalScore"].reset(new PersistentValue<float>(0));

	LoadEditorScene("Scene1");
}

void Engine::Update()
{
	mGraphics->BeginFrame();

	// If game is playing
	UpdateScene();
	DrawScene();

	mGraphics->EndFrame();

	Audio::Instance().Update();
}

Engine::~Engine()
{
	mScene = nullptr;
	mGraphics->Destroy();
}

void Engine::UpdateScene()
{
	float deltaTime = mFrameTimer.Mark();

	if (EngineState == EngineState::ePlayMode)
	{
		if (SceneManagement::Instance().LoadNewScene)
		{
			LoadPlayScene(SceneManagement::Instance().NewSceneName);
		}
	}
	
	mScene->Update(deltaTime);
}

void Engine::DrawScene()
{
	mScene->Draw();
}

void Engine::LoadPlayScene(std::string sceneName)
{
	mScene = nullptr;
	SceneManagement::Instance().LoadNewScene = false;

	stringstream stream;
	stream << ApplicationValues::Instance().ResourcesPath + "\\Levels\\" + sceneName + ".xml";
	string scenePath = stream.str();

	EngineState = EngineState::ePlayMode;

	mScene = make_shared<PlayScene>(new PlayCamera(mGraphics));
	SceneBuilder::BuildScene(mScene, scenePath);
}

void Engine::LoadEditorScene(std::string sceneName)
{
	mScene = nullptr;

	stringstream stream;
	stream << ApplicationValues::Instance().ResourcesPath + "\\Levels\\" + sceneName + ".xml";
	string scenePath = stream.str();

	EngineState = EngineState::eEditor;

	mScene = make_shared<EditorScene>(new EditorCamera(mGraphics));
	SceneBuilder::BuildScene(mScene, scenePath);
}
