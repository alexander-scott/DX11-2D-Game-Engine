#include "DamageableComponent.h"

DamageableComponent::DamageableComponent(float startHealth)
{
	_type = "Damageable Component";
	_health = startHealth;
	_isDead = false;
}

DamageableComponent::~DamageableComponent()
{
}

void DamageableComponent::RecieveDamage(float dmg)
{
	_health -= dmg;

	if (_health <= 0)
	{
		_health = 0;
		_isDead = true;
	}
}

void DamageableComponent::RecieveMessage(IMessage & msg)
{
	switch (msg.GetType())
	{
		case MessageType::eRecieveDamage:
			RecieveDamageMessage& recieveDmgMsg = static_cast<RecieveDamageMessage &> (msg);
			RecieveDamage(recieveDmgMsg._damage);
			break;
	}
}
