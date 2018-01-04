#include "GameStartScreen.h"

GameStartScreen::GameStartScreen()
{
	BuildStartScreen();
}

GameStartScreen::~GameStartScreen()
{
}

void GameStartScreen::UpdateGUI(float deltaTime)
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

void GameStartScreen::DrawGUI()
{
	// Draw gameobjects
	for (auto& go : mGameObjects)
	{
		go->Draw(&GameCamera::Instance());
	}
}

void GameStartScreen::BuildStartScreen()
{
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
	centreButtonText->AddComponent(ComponentFactory::MakeGUIText("Play", DirectX::Colors::White, restartTransform, Vec2(90, 30))); // HARDCODED POSTION
	mGameObjects.push_back(centreButtonText);

	GameObject* skyBackground = new GameObject("SkyBackground");
	TransformComponent* skyTrans = ComponentFactory::MakeTransform(Vec2(0, 0), 0, 1);
	skyBackground->AddComponent(skyTrans);
	TiledBGRenderer* skyRenderer = ComponentFactory::MakeTiledBGRenderer("BG_Sky", 640, 480, 0.1f, TiledBGDirection::eHoriztonalAndVertical, skyTrans, buttonTransform);
	skyBackground->AddComponent(skyRenderer);
	mGameObjects.push_back(skyBackground);

	GameObject* vegBackground = new GameObject("VegBackground");
	TransformComponent* vegTrans = ComponentFactory::MakeTransform(Vec2(0, -400), 0, 1);
	vegBackground->AddComponent(vegTrans);
	TiledBGRenderer* vegRenderer = ComponentFactory::MakeTiledBGRenderer("BG_Vegetation", 640, 480, 0.5f, TiledBGDirection::eHorizontal, vegTrans, buttonTransform);
	vegBackground->AddComponent(vegRenderer);
	mGameObjects.push_back(vegBackground);

	GameObject* groundBackground = new GameObject("GroundBackground");
	TransformComponent* groundTrans = ComponentFactory::MakeTransform(Vec2(0, -400), 0, 1);
	groundBackground->AddComponent(groundTrans);
	TiledBGRenderer* groundRenderer = ComponentFactory::MakeTiledBGRenderer("BG_Ground", 640, 480, 3, TiledBGDirection::eHorizontal, groundTrans, buttonTransform);
	groundBackground->AddComponent(groundRenderer);
	mGameObjects.push_back(groundBackground);
}
