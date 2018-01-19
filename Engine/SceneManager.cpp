#include "SceneManager.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	mScene = nullptr;
}

void SceneManager::LoadScene(std::string sceneName)
{
	mScene = nullptr;

	stringstream stream;
	stream << ApplicationValues::Instance().ResourcesPath + "\\Levels\\" + sceneName + ".xml";
	string scenePath = stream.str();

	mScene = SceneBuilder::BuildScene(scenePath);
}

void SceneManager::Update(float deltaTime)
{
	if (mScene == nullptr)
		return;

	mScene->Update(deltaTime);
}

void SceneManager::Draw()
{
	if (mScene == nullptr)
		return;

	mScene->Draw();
}