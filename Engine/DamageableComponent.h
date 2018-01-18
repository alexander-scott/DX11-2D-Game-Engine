#pragma once

#include "IComponent.h"
#include "IMessageable.h"

#include "RecieveDamageMessage.h"

#include "Audio.h"

class DamageableComponent : public IComponent, public IMessageable
{
public:
	DamageableComponent(float startHealth, std::string hitNoise);
	~DamageableComponent();

	void RecieveDamage(float dmg);
	virtual void RecieveMessage(IMessage &msg) override;

	bool IsDead() { return mIsDead; }

	float				Health;

private:
	bool				mIsDead;
	std::string			mHitNoise;
};