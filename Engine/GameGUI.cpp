#include "GameGUI.h"

GameGUI::GameGUI(GameLevel* gameLevel) : mGameLevel(gameLevel)
{
	GameObject* scoreText = new GameObject("Text");
	TransformComponent* scoreTransform = ComponentFactory::MakeTransform(Vec2(10, 10), 0, 0.5f);
	scoreText->AddComponent(scoreTransform);
	scoreText->AddComponent(ComponentFactory::MakeGUITextValueComponent("Score:", DirectX::Colors::Yellow, scoreTransform, mGameLevel->Score));
	mGameObjects.push_back(scoreText);

	GameObject* healthText = new GameObject("Text");
	TransformComponent* healthTransform = ComponentFactory::MakeTransform(Vec2(SCREEN_WIDTH - 130, 10), 0, 0.5f);
	healthText->AddComponent(healthTransform);
	healthText->AddComponent(ComponentFactory::MakeGUITextValueComponent("Health:", DirectX::Colors::Red, healthTransform, mGameLevel->FindGameObject("Player")->GetComponent<DamageableComponent>()->GetHealthAddress()));
	mGameObjects.push_back(healthText);
}

GameGUI::~GameGUI()
{
	for (auto& go : mGameObjects)
	{
		if (go)
		{
			delete go;
		}
	}
}

void GameGUI::DrawGUI()
{
	// Draw gameobjects
	for (auto& go : mGameObjects)
	{
		go->Draw(&GameCamera::Instance());
	}
}

void GameGUI::UpdateGUI(float deltaTime)
{
	for (auto& go : mGameObjects)
	{
		go->Update(deltaTime);
	}
}
