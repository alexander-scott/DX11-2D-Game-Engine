#include "GameComponentFactory.h"


PlayerComponent * ComponentFactory::MakePlayerComponent(TransformComponent* trans, SpriteAnimatorComponent * anim, RigidBodyComponent * rb, DamageableComponent* dmg, ProjectileManager* proj)
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

	PlayerComponent* playerComponent = new PlayerComponent(trans, anim, rb, dmg, proj);

	return playerComponent;
}

DamageableComponent * ComponentFactory::MakeDamageableComponent(float startHealth)
{
	DamageableComponent* damageComponent = new DamageableComponent(startHealth);
	return damageComponent;
}

ProjectileComponent * ComponentFactory::MakeProjectileComponent(std::string affectedTag, float lifeSpan, float dmg)
{
	ProjectileComponent* projectileComponent = new ProjectileComponent(affectedTag, lifeSpan, dmg);
	return projectileComponent;
}
