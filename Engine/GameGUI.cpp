#include "GameGUI.h"

GameGUI::GameGUI(GameLevel* gameLevel) : mGameLevel(gameLevel)
{
	mCentreButtonClicked = false;
	BuildGUI();
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

void GameGUI::BuildGUI()
{
	// Score Text
	GameObject* scoreText = new GameObject("ScoreText");
	TransformComponent* scoreTransform = ComponentFactory::MakeTransform(Vec2(10, 10), 0, 0.5f);
	scoreText->AddComponent(scoreTransform);
	scoreText->AddComponent(ComponentFactory::MakeGUITextValueComponent("Score:", DirectX::Colors::Yellow, scoreTransform, mGameLevel->Score));
	mGameObjects.push_back(scoreText);

	// Health Text
	GameObject* healthText = new GameObject("HealthText");
	TransformComponent* healthTransform = ComponentFactory::MakeTransform(Vec2(SCREEN_WIDTH - 130, 10), 0, 0.5f);
	healthText->AddComponent(healthTransform);
	healthText->AddComponent(ComponentFactory::MakeGUITextValueComponent("Health:", DirectX::Colors::Red, healthTransform, mGameLevel->FindGameObject("Player")->GetComponent<DamageableComponent>()->GetHealthAddress()));
	mGameObjects.push_back(healthText);

	// Centre Button sprite and button
	mCentreButtonSprite = new GameObject("CentreButton");
	TransformComponent* buttonTransform = ComponentFactory::MakeTransform(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0, 1);
	mCentreButtonSprite->AddComponent(buttonTransform);
	mCentreButtonSprite->AddComponent(ComponentFactory::MakeGUISpriteRenderer("GUIButton", buttonTransform, 239, 131, Vec2(0, 0)));
	mCentreButton = ComponentFactory::MakeGUIButton(buttonTransform, 239, 131);
	mCentreButtonSprite->AddComponent(mCentreButton);
	mCentreButtonSprite->SetActive(false); // Set inactive
	mGameObjects.push_back(mCentreButtonSprite);

	// Centre button text
	mCentreButtonText = new GameObject("RestartText");
	TransformComponent* restartTransform = ComponentFactory::MakeTransform(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0, 1);
	mCentreButtonText->AddComponent(restartTransform);
	mCentreButtonText->AddComponent(ComponentFactory::MakeGUIText("RESTART", DirectX::Colors::White, restartTransform, Vec2(90, 30))); // HARDCODED POSTION
	mCentreButtonText->SetActive(false); // Set inactive
	mGameObjects.push_back(mCentreButtonText);
}

void GameGUI::DrawGUI()
{
	// Draw gameobjects
	for (auto& go : mGameObjects)
	{
		go->Draw(&GameCamera::Instance());
	}
}

void GameGUI::EnableCentreButton(std::string buttonText)
{
	mCentreButtonSprite->SetActive(true);
	mCentreButtonText->SetActive(true);

	mCentreButtonText->GetComponent<GUITextComponent>()->SetText(buttonText);
}

void GameGUI::UpdateGUI(float deltaTime)
{
	if (mCentreButtonClicked)
		return;

	for (auto& go : mGameObjects)
	{
		go->Update(deltaTime);
	}

	if (mCentreButton->Clicked())
	{
		mCentreButtonClicked = true;
	}
}
