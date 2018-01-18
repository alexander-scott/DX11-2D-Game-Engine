#include "GameGUI.h"

GameGUI::GameGUI()
{
	mCentreButtonClicked = false;
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
