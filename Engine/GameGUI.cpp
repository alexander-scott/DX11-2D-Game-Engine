#include "GameGUI.h"

GameGUI::GameGUI()
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
	mGameObjects.push_back(scoreText);

	// Level Text
	GameObject* levelText = new GameObject("LevelText");
	TransformComponent* levelTransform = ComponentFactory::MakeTransform(Vec2(10, 35), 0, 0.5f);
	levelText->AddComponent(ComponentFactory::MakeGUIText("", DirectX::Colors::Blue, levelTransform, Vec2(0, 0)));
	levelText->AddComponent(levelTransform);
	mGameObjects.push_back(levelText);

	// Health Text
	GameObject* healthText = new GameObject("HealthText");
	TransformComponent* healthTransform = ComponentFactory::MakeTransform(Vec2(SCREEN_WIDTH - 130, 10), 0, 0.5f);
	healthText->AddComponent(healthTransform);
	mGameObjects.push_back(healthText);

	// Centre Button sprite and button
	GameObject* centreButtonSprite = new GameObject("CentreButton");
	TransformComponent* buttonTransform = ComponentFactory::MakeTransform(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0, 1);
	centreButtonSprite->AddComponent(buttonTransform);
	centreButtonSprite->AddComponent(ComponentFactory::MakeGUISpriteRenderer("GUIButton", buttonTransform, 239, 131, Vec2(0, 0)));
	mCentreButton = ComponentFactory::MakeGUIButton(buttonTransform, 239, 131);
	centreButtonSprite->AddComponent(mCentreButton);
	mGameObjects.push_back(centreButtonSprite);

	// Centre button text
	GameObject* centreButtonText = new GameObject("CentreButtonText");
	TransformComponent* restartTransform = ComponentFactory::MakeTransform(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0, 1);
	centreButtonText->AddComponent(restartTransform);
	centreButtonText->AddComponent(ComponentFactory::MakeGUIText("", DirectX::Colors::White, restartTransform, Vec2(90, 30))); // HARDCODED POSTION
	mGameObjects.push_back(centreButtonText);
}

void GameGUI::DrawGUI()
{
	// Draw gameobjects
	for (auto& go : mGameObjects)
	{
		go->Draw(&GameCamera::Instance());
	}
}

void GameGUI::ResetGUI(GameLevel* gameLevel, int currentLevel)
{
	// Update score references
	GameObject* scoreText = FindGameObject("ScoreText");
	scoreText->RemoveComponent<GUITextValueComponent>();
	scoreText->AddComponent(ComponentFactory::MakeGUITextValueComponent("Score:", DirectX::Colors::Blue, scoreText->GetComponent<TransformComponent>(), gameLevel->Score));

	// Update level text
	GameObject* levelText = FindGameObject("LevelText");
	levelText->GetComponent<GUITextComponent>()->SetText("Level:" + std::to_string(currentLevel));

	// Update health references
	GameObject* healthText = FindGameObject("HealthText");
	healthText->RemoveComponent<GUITextValueComponent>();
	healthText->AddComponent(ComponentFactory::MakeGUITextValueComponent("Health:", DirectX::Colors::Red, healthText->GetComponent<TransformComponent>(), gameLevel->FindGameObject("Player")->GetComponent<DamageableComponent>()->GetHealthAddress()));

	FindGameObject("CentreButton")->SetActive(false);
	FindGameObject("CentreButtonText")->SetActive(false);

	mCentreButton->Reset();
	mCentreButtonClicked = false;
}

void GameGUI::EnableCentreButton(std::string buttonText)
{
	FindGameObject("CentreButton")->SetActive(true);

	GameObject* textObj = FindGameObject("CentreButtonText");
	textObj->SetActive(true);
	textObj->GetComponent<GUITextComponent>()->SetText(buttonText);
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

GameObject* GameGUI::FindGameObject(std::string tag)
{
	for (auto& go : mGameObjects)
	{
		if (go->GetTag() == tag)
			return go;
	}

	return nullptr;
}
