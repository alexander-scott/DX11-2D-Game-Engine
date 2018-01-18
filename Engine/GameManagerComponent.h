#pragma once

#include "IComponent.h"
#include "IUpdateable.h"

#include "GUIButtonComponent.h"
#include "GUITextComponent.h"
#include "GUISpriteRendererComponent.h"

#include "TriggerBoxComponent.h"
#include "DamageableComponent.h"

#include "Audio.h"

class GameManagerComponent : public IComponent, public IUpdateable
{
public:
	GameManagerComponent(GUIButtonComponent* centreButton, GUITextComponent* centreButtonText, GUISpriteRendererComponent* centreButtonSprite,
		TriggerBoxComponent* finishTriggerBox, DamageableComponent* playerDamage);
	~GameManagerComponent();

	virtual void Update(float deltaTime) override;

private:
	GUIButtonComponent*			mCentreButton;
	GUITextComponent*			mCentreButtonText;
	GUISpriteRendererComponent*	mCentreButtonSprite;

	TriggerBoxComponent*		mFinishTriggerBox;
	DamageableComponent*		mPlayerDamage;

	bool						mWaitingOnInput;
};

