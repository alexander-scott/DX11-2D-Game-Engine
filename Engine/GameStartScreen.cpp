#include "GameStartScreen.h"

GameStartScreen::GameStartScreen()
{
	mCentreButtonClicked = false;
	BuildStartScreen();
}

GameStartScreen::~GameStartScreen()
{
	for (auto& go : mGameObjects)
	{
		if (go)
		{
			go = nullptr;
		}
	}
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
	auto centreButtonSpriteGO = GameObject::MakeGameObject("CentreButton");
	TransformComponent* buttonTransform = ComponentFactory::MakeTransform(Vec2(ApplicationValues::Instance().ScreenWidth / 2, ApplicationValues::Instance().ScreenHeight / 2), 0, 1);
	centreButtonSpriteGO->AddComponent(buttonTransform);
	centreButtonSpriteGO->AddComponent(ComponentFactory::MakeGUISpriteRenderer("GUIButton", buttonTransform, 239, 131, Vec2(0, 0)));
	mCentreButton = ComponentFactory::MakeGUIButton(buttonTransform, 239, 131);
	centreButtonSpriteGO->AddComponent(mCentreButton);

	// Centre button text
	auto centreButtonTextGO = GameObject::MakeGameObject("CentreButtonText");
	TransformComponent* restartTransform = ComponentFactory::MakeTransform(Vec2(ApplicationValues::Instance().ScreenWidth / 2, ApplicationValues::Instance().ScreenHeight / 2), 0, 1);
	centreButtonTextGO->AddComponent(restartTransform);
	centreButtonTextGO->AddComponent(ComponentFactory::MakeGUIText("PLAY", DirectX::Colors::White, restartTransform, Vec2(60, 30))); // HARDCODED POSTION

	auto skyBackgroundGO = GameObject::MakeGameObject("SkyBackground");
	TransformComponent* skyTrans = ComponentFactory::MakeTransform(Vec2(0, 0), 0, 1);
	skyBackgroundGO->AddComponent(skyTrans);
	TiledBGRenderer* skyRenderer = ComponentFactory::MakeTiledBGRenderer("BG_Sky", 640, 480, 0.1f, TiledBGDirection::eHoriztonalAndVertical, skyTrans, buttonTransform);
	skyBackgroundGO->AddComponent(skyRenderer);

	mGameObjects.push_back(skyBackgroundGO);
	mGameObjects.push_back(centreButtonSpriteGO);
	mGameObjects.push_back(centreButtonTextGO);
}
