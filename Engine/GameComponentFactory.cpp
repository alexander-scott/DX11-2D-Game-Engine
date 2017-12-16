#include "GameComponentFactory.h"


PlayerComponent * ComponentFactory::MakePlayerComponent(TransformComponent* trans, SpriteAnimatorComponent * anim, RigidBodyComponent * rb, DamageableComponent* dmg)
{
	if (anim == nullptr)
	{
		throw std::exception("This object requires a animator component.");
	}

	if (rb == nullptr)
	{
		throw std::exception("This object requires a rigidbody component.");
	}

	if (dmg == nullptr)
	{
		throw std::exception("This object requires a damageable component.");
	}

	PlayerComponent* playerComponent = new PlayerComponent(trans, anim, rb, dmg);

	return playerComponent;
}

DamageableComponent * ComponentFactory::MakeDamageableComponent(float startHealth)
{
	DamageableComponent* damageComponent = new DamageableComponent(startHealth);
	return damageComponent;
}
