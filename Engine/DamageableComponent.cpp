#include "DamageableComponent.h"

DamageableComponent::DamageableComponent(float startHealth)
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
