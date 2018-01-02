#pragma once

#include "IComponent.h"
#include "IMessageable.h"

#include "RecieveDamageMessage.h"

class DamageableComponent : public IComponent, public IMessageable
{
public:
	DamageableComponent(float startHealth);
	~DamageableComponent();

	void RecieveDamage(float dmg);
	virtual void RecieveMessage(IMessage &msg) override;

	bool IsDead() { return mIsDead; }

private:
	float				mHealth;
	bool				mIsDead;
};