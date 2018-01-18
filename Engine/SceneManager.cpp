#include "SceneManager.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::LoadScene(std::string sceneName)
{
	mGameLevel = nullptr;

	stringstream stream;
	//stream << ApplicationValues::Instance().ResourcesPath + "\\Levels\\Level" << ScenePersistentValues::Instance().GetValue<float>("CurrentLevel") << ".xml";
	stream << ApplicationValues::Instance().ResourcesPath + "\\Levels\\Scene.xml";
	string levelPath = stream.str();

	mGameLevel = SceneBuilder::BuildScene(levelPath);
}

void SceneManager::Update(float deltaTime)
{
	if (mGameLevel == nullptr)
		return;

	mGameLevel->Update(deltaTime);
}

void SceneManager::Draw()
{
	if (mGameLevel == nullptr)
		return;

	mGameLevel->Draw();
}