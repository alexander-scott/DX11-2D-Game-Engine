#include "GameManagerComponent.h"

GameManagerComponent::GameManagerComponent(GUIButtonComponent* centreButton, GUITextComponent* centreButtonText, GUISpriteRendererComponent* centreButtonSprite, TriggerBoxComponent* finishTriggerBox, DamageableComponent* playerDamage)
	: mCentreButton(centreButton), mCentreButtonText(centreButtonText), mCentreButtonSprite(centreButtonSprite), mFinishTriggerBox(finishTriggerBox), mPlayerDamage(playerDamage)
{
	mWaitingOnInput = false;
}

GameManagerComponent::~GameManagerComponent()
{
}

void GameManagerComponent::Update(float deltaTime)
{
	if (mWaitingOnInput)
	{
		if (mCentreButton->Clicked())
		{
			float currenLevel = ScenePersistentValues::Instance().GetValue<float>("CurrentLevel");
			currenLevel++;
			ScenePersistentValues::Instance().Values["CurrentLevel"].reset(new PersistentValue<float>(currenLevel));

			stringstream stream;
			stream << "Scene" << currenLevel;
			ISceneManager::Instance().LoadScene(stream.str());
		}

		return;
	}

	if (mPlayerDamage->IsDead())
	{
		mCentreButton->SetActive(true);

		mCentreButtonText->SetActive(true);
		mCentreButtonText->SetText("RESTART");

		mCentreButtonSprite->SetActive(true);
		mWaitingOnInput = true;
	}
	else if (mFinishTriggerBox->IsTriggered())
	{
		mCentreButton->SetActive(true);

		mCentreButtonText->SetActive(true);
		mCentreButtonText->SetText("PROGRESS");

		mCentreButtonSprite->SetActive(true);
		mWaitingOnInput = true;

		Audio::Instance().PlaySoundEffect("Win");
	}
}