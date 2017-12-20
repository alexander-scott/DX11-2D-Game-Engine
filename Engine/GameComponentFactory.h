#pragma once

#include "ComponentFactory.h"

#include "PlayerComponent.h"
#include "DamageableComponent.h"
#include "ProjectileComponent.h"
#include "AIAgentComponent.h"

#include "ProjectileManager.h"

namespace ComponentFactory
{
	PlayerComponent * MakePlayerComponent(TransformComponent* trans, SpriteAnimatorComponent* anim, RigidBodyComponent* rb, DamageableComponent* dmg, ProjectileManager* proj, TransformComponent* cameraTransform);
	DamageableComponent * MakeDamageableComponent(float startHealth);
	ProjectileComponent * MakeProjectileComponent(std::string affectedTag, float lifeSpan, float dmg);
	AIAgentComponent * MakeAIAgentComponent(TransformComponent* trans, SpriteAnimatorComponent* anim, RigidBodyComponent* rb, DamageableComponent* dmg, ProjectileManager* proj, TransformComponent* cameraTransform, float patrolTime, AIAgentPatrolDirection patrolStartDir, float idleTime);
}

