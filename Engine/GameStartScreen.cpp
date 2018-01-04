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
			delete go;
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
	GameObject* centreButtonSprite = new GameObject("CentreButton");
	TransformComponent* buttonTransform = ComponentFactory::MakeTransform(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0, 1);
	centreButtonSprite->AddComponent(buttonTransform);
	centreButtonSprite->AddComponent(ComponentFactory::MakeGUISpriteRenderer("GUIButton", buttonTransform, 239, 131, Vec2(0, 0)));
	mCentreButton = ComponentFactory::MakeGUIButton(buttonTransform, 239, 131);
	centreButtonSprite->AddComponent(mCentreButton);

	// Centre button text
	GameObject* centreButtonText = new GameObject("CentreButtonText");
	TransformComponent* restartTransform = ComponentFactory::MakeTransform(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0, 1);
	centreButtonText->AddComponent(restartTransform);
	centreButtonText->AddComponent(ComponentFactory::MakeGUIText("PLAY", DirectX::Colors::White, restartTransform, Vec2(60, 30))); // HARDCODED POSTION

	GameObject* skyBackground = new GameObject("SkyBackground");
	TransformComponent* skyTrans = ComponentFactory::MakeTransform(Vec2(0, 0), 0, 1);
	skyBackground->AddComponent(skyTrans);
	TiledBGRenderer* skyRenderer = ComponentFactory::MakeTiledBGRenderer("BG_Sky", 640, 480, 0.1f, TiledBGDirection::eHoriztonalAndVertical, skyTrans, buttonTransform);
	skyBackground->AddComponent(skyRenderer);
	mGameObjects.push_back(skyBackground);

	mGameObjects.push_back(centreButtonSprite);
	mGameObjects.push_back(centreButtonText);
}
