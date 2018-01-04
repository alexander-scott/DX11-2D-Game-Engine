#include "GameGUI.h"

GameGUI::GameGUI(GameLevel* gameLevel) : mGameLevel(gameLevel)
{
	GameObject* scoreText = new GameObject("ScoreText");
	TransformComponent* scoreTransform = ComponentFactory::MakeTransform(Vec2(10, 10), 0, 0.5f);
	scoreText->AddComponent(scoreTransform);
	scoreText->AddComponent(ComponentFactory::MakeGUITextValueComponent("Score:", DirectX::Colors::Yellow, scoreTransform, mGameLevel->Score));
	mGameObjects.push_back(scoreText);

	GameObject* healthText = new GameObject("HealthText");
	TransformComponent* healthTransform = ComponentFactory::MakeTransform(Vec2(SCREEN_WIDTH - 130, 10), 0, 0.5f);
	healthText->AddComponent(healthTransform);
	healthText->AddComponent(ComponentFactory::MakeGUITextValueComponent("Health:", DirectX::Colors::Red, healthTransform, mGameLevel->FindGameObject("Player")->GetComponent<DamageableComponent>()->GetHealthAddress()));
	mGameObjects.push_back(healthText);

	GameObject* centreButton = new GameObject("CentreButton");
	TransformComponent* buttonTransform = ComponentFactory::MakeTransform(Vec2(SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 2), 0, 1);
	centreButton->AddComponent(buttonTransform);
	centreButton->AddComponent(ComponentFactory::MakeGUISpriteRenderer("GUIButton", buttonTransform, 239, 131, Vec2(0, 0)));
	centreButton->AddComponent(ComponentFactory::MakeGUIButton(buttonTransform, 239, 131));
	mGameObjects.push_back(centreButton);

	GameObject* restartText = new GameObject("RestartText");
	TransformComponent* restartTransform = ComponentFactory::MakeTransform(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0, 1);
	restartText->AddComponent(restartTransform);
	restartText->AddComponent(ComponentFactory::MakeGUIText("RESTART", DirectX::Colors::White, restartTransform));
	mGameObjects.push_back(restartText);
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
