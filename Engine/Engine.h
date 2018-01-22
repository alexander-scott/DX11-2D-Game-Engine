#pragma once

#include "FrameTimer.h"
#include "MainWindow.h"

#include "SceneBuilder.h"
#include "SceneManagement.h"
#include "ScenePersistentValues.h"

#include "PlayScene.h"
#include "PlayCamera.h"

#include "EditorScene.h"
#include "EditorCamera.h"

using namespace std;

class Engine
{
public:
	Engine(class MainWindow& wnd, int width, int height, std::string resourcesPath);
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

	shared_ptr<IScene> GetScene();

	void PlayStarted();
	void PlayStopped();

	void Update();

	~Engine();

	MainWindow& wnd;

	EngineState EngineState;

private:
	void DrawScene();
	void UpdateScene();

	void LoadPlayScene(std::string sceneName);
	void InitaliseEditorScene(std::string sceneName);

	FrameTimer					mFrameTimer;
	shared_ptr<IScene>			mEditorScene;
	shared_ptr<IScene>			mPlayScene;
	IGraphics*					mGraphics;
};