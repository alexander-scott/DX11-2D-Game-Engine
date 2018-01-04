#include "DamageableComponent.h"

DamageableComponent::DamageableComponent(float startHealth, std::string hitNoise) : mHitNoise(hitNoise)
{
	mType = "Damageable Component";
	mHealth = startHealth;
	mIsDead = false;
}

DamageableComponent::~DamageableComponent()
{
}

void DamageableComponent::RecieveDamage(float dmg)
{
	mHealth -= dmg;

	if (mHealth <= 0)
	{
		mHealth = 0;
		mIsDead = true;
	}
	else
	{
		if (mHitNoise != "")
		{
			Audio::Instance().PlaySoundEffect(mHitNoise);
		}
	}
}

void DamageableComponent::RecieveMessage(IMessage & msg)
{
	switch (msg.GetType())
	{
		case MessageType::eRecieveDamage:
			RecieveDamageMessage& recieveDmgMsg = static_cast<RecieveDamageMessage &> (msg);
			RecieveDamage(recieveDmgMsg.Damage);
			break;
	}
}
