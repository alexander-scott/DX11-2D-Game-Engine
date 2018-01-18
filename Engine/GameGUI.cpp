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
			go = nullptr;
		}
	}
}

void GameGUI::BuildGUI()
{
	// Score Text
	auto scoreText = GameObject::MakeGameObject("ScoreText");
	TransformComponent* scoreTransform = ComponentFactory::MakeTransform(Vec2(10, 10), 0, 0.5f);
	scoreText->AddComponent(scoreTransform);
	mGameObjects.push_back(scoreText);

	// Level Text
	auto levelText = GameObject::MakeGameObject("LevelText");
	TransformComponent* levelTransform = ComponentFactory::MakeTransform(Vec2(10, 35), 0, 0.5f);
	levelText->AddComponent(ComponentFactory::MakeGUIText("", DirectX::Colors::Blue, levelTransform, Vec2(0, 0)));
	levelText->AddComponent(levelTransform);
	mGameObjects.push_back(levelText);

	// Health Text
	auto healthText = GameObject::MakeGameObject("HealthText");
	TransformComponent* healthTransform = ComponentFactory::MakeTransform(Vec2((float)ApplicationValues::Instance().ScreenWidth - 130, 10), 0, 0.5f);
	healthText->AddComponent(healthTransform);
	mGameObjects.push_back(healthText);

	// Centre Button sprite and button
	auto centreButtonSprite = GameObject::MakeGameObject("CentreButton");
	TransformComponent* buttonTransform = ComponentFactory::MakeTransform(Vec2((float)ApplicationValues::Instance().ScreenWidth / 2, (float)ApplicationValues::Instance().ScreenHeight / 2), 0, 1);
	centreButtonSprite->AddComponent(buttonTransform);
	centreButtonSprite->AddComponent(ComponentFactory::MakeGUISpriteRenderer("GUIButton", 3, buttonTransform, 239, 131, Vec2(0, 0)));
	mCentreButton = ComponentFactory::MakeGUIButton(buttonTransform, 239, 131);
	centreButtonSprite->AddComponent(mCentreButton);
	mGameObjects.push_back(centreButtonSprite);

	// Centre button text
	auto centreButtonText = GameObject::MakeGameObject("CentreButtonText");
	TransformComponent* restartTransform = ComponentFactory::MakeTransform(Vec2((float)ApplicationValues::Instance().ScreenWidth / 2, (float)ApplicationValues::Instance().ScreenHeight / 2), 0, 1);
	centreButtonText->AddComponent(restartTransform);
	centreButtonText->AddComponent(ComponentFactory::MakeGUIText("", DirectX::Colors::White, restartTransform, Vec2(90, 30))); // HARDCODED POSTION
	mGameObjects.push_back(centreButtonText);
}

void GameGUI::ResetGUI(std::shared_ptr<GameLevel> gameLevel, int currentLevel)
{
	// Update score references
	auto scoreTextGO = FindGameObject("ScoreText");
	scoreTextGO->RemoveComponent<GUITextValueComponent>();
	scoreTextGO->AddComponent(ComponentFactory::MakeGUITextValueComponent("Score:", DirectX::Colors::Blue, scoreTextGO->GetComponent<TransformComponent>(), gameLevel->GetScore()));

	// Update level text
	auto levelTextGO = FindGameObject("LevelText");
	levelTextGO->GetComponent<GUITextComponent>()->SetText("Level:" + std::to_string(currentLevel));

	// Update health references
	auto healthTextGO = FindGameObject("HealthText");
	healthTextGO->RemoveComponent<GUITextValueComponent>();
	healthTextGO->AddComponent(ComponentFactory::MakeGUITextValueComponent("Health:", DirectX::Colors::Red, healthTextGO->GetComponent<TransformComponent>(), gameLevel->FindGameObject("Player")->GetComponent<DamageableComponent>()->GetHealthAddress()));

	FindGameObject("CentreButton")->SetActive(false);
	FindGameObject("CentreButtonText")->SetActive(false);

	mCentreButton->Reset();
	mCentreButtonClicked = false;
}

void GameGUI::EnableCentreButton(std::string buttonText)
{
	FindGameObject("CentreButton")->SetActive(true);

	auto textGO = FindGameObject("CentreButtonText");
	textGO->SetActive(true);
	textGO->GetComponent<GUITextComponent>()->SetText(buttonText);
}

void GameGUI::DrawGUI()
{
	// Draw gameobjects
	for (auto& go : mGameObjects)
	{
		go->Draw(&Camera::Instance());
	}
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
		Audio::Instance().PlaySoundEffect("Tap");
		mCentreButtonClicked = true;
	}
}

shared_ptr<GameObject> GameGUI::FindGameObject(std::string tag)
{
	for (auto& go : mGameObjects)
	{
		if (go->GetTag() == tag)
			return go;
	}

	return nullptr;
}
