#include "GameComponentFactory.h"


PlayerComponent * ComponentFactory::MakePlayerComponent(TransformComponent* trans, SpriteAnimatorComponent * anim, 
	RigidBodyComponent * rb, DamageableComponent* dmg, ProjectileManager* proj, TransformComponent* cameraTrans)
{
	if (trans == nullptr)
	{
		throw std::exception("This object requires a transform component.");
	}
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
	if (proj == nullptr)
	{
		throw std::exception("This object requires a projectile manager component.");
	}
	if (cameraTrans == nullptr)
	{
		throw std::exception("This object requires a camera transform.");
	}

	PlayerComponent* playerComponent = new PlayerComponent(trans, anim, rb, dmg, proj, cameraTrans);

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

AIAgentComponent * ComponentFactory::MakeAIAgentComponent(TransformComponent * trans, SpriteAnimatorComponent * anim, RigidBodyComponent * rb, DamageableComponent * dmg, 
	ProjectileManager * proj, TransformComponent * cameraTransform, float patrolTime, AIAgentPatrolDirection patrolStartDir, float idleTime)
{
	if (trans == nullptr)
	{
		throw std::exception("This object requires a transform component.");
	}
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
	if (proj == nullptr)
	{
		throw std::exception("This object requires a projectile manager component.");
	}
	if (cameraTransform == nullptr)
	{
		throw std::exception("This object requires a camera transform.");
	}

	AIAgentComponent* agentComponent = new AIAgentComponent(trans, anim, rb, dmg, proj, cameraTransform, patrolTime, patrolStartDir, idleTime);

	return agentComponent;
}