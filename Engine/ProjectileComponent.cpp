#include "ProjectileComponent.h"

ProjectileComponent::ProjectileComponent(std::string affectedTag, float lifeSpan, float dmg)
{
	_affectedTag = affectedTag;
	_lifeLeft = lifeSpan;
	_damage = dmg;
}

ProjectileComponent::~ProjectileComponent()
{
}

void ProjectileComponent::RecieveMessage(IMessage & msg)
{
	switch (msg.GetType())
	{
	case MessageType::eCollision:
		CollisionMessage& colMsg = static_cast<CollisionMessage &> (msg);
		if (colMsg.collidedObject->GetTag() == _affectedTag)
		{
			RecieveDamageMessage recieveDmg(_damage);
			colMsg.collidedObject->SendMessageToComponents(recieveDmg);
			_isDead = true;
		}

		break;
	}
}

void ProjectileComponent::Update(float deltaTime)
{
	_lifeLeft -= deltaTime;
	if (_lifeLeft < 0)
	{
		_isDead = true;
	}
}
