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

	//SceneBuilder::InitaliseGameplayValues(ApplicationValues::Instance().ResourcesPath + "\\Levels\\Prefabs.xml"); //BROKEN

	ScenePersistentValues::Instance().Values["CurrentLevel"].reset(new PersistentValue<float>(1));
	ScenePersistentValues::Instance().Values["TotalScore"].reset(new PersistentValue<float>(0));

	InitaliseEditorScene("");
}

shared_ptr<IScene> Engine::GetScene()
{
	if (EngineState == EngineState::ePlayMode)
	{
		return mPlayScene;
	}
	else
	{
		return mEditorScene;
	}
}

void Engine::PlayStarted()
{
	LoadPlayScene("Scene1");
}

void Engine::PlayStopped()
{
	mPlayScene = nullptr;
	EngineState = EngineState::eEditor;
}

void Engine::LoadNewScene(std::string scenePath)
{
	InitaliseEditorScene(scenePath);
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
	mEditorScene = nullptr;
	mPlayScene = nullptr;

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
		mPlayScene->Update(deltaTime);
	}
	else
	{
		mEditorScene->Update(deltaTime);
	}
}

void Engine::DrawScene()
{
	if (EngineState == EngineState::ePlayMode)
	{
		mPlayScene->Draw();
	}
	else
	{
		mEditorScene->Draw();
	}	
}

void Engine::LoadPlayScene(std::string sceneName)
{
	SceneManagement::Instance().LoadNewScene = false;

	stringstream stream;
	stream << ApplicationValues::Instance().ResourcesPath + "\\Levels\\" + sceneName + ".xml";
	string scenePath = stream.str();

	EngineState = EngineState::ePlayMode;

	mPlayScene = make_shared<PlayScene>(new PlayCamera(mGraphics));
	SceneBuilder::BuildScene(mPlayScene, scenePath);
}

void Engine::InitaliseEditorScene(std::string sceneName)
{
	EngineState = EngineState::eEditor;

	mEditorScene = make_shared<EditorScene>(new EditorCamera(mGraphics));

	if (!sceneName.empty())
	{
		SceneBuilder::BuildScene(mEditorScene, sceneName);
	}
}