#pragma once

#include "ComponentFactory.h"

#include "PlayerComponent.h"
#include "DamageableComponent.h"
#include "ProjectileComponent.h"
#include "AIAgentComponent.h"
#include "ProjectileManagerComponent.h"
#include "GUITextValueComponent.h"
#include "GUITextDamageComponent.h"
#include "GameCameraComponent.h"

namespace ComponentFactory
{
	PlayerComponent * MakePlayerComponent(TransformComponent* trans, SpriteAnimatorComponent* anim, RigidBodyComponent* rb, DamageableComponent* dmg, ProjectileManagerComponent* proj, TransformComponent* cameraTransform);
	
	DamageableComponent * MakeDamageableComponent(float startHealth, std::string hitNoise);
	
	ProjectileComponent * MakeProjectileComponent(std::string affectedTag, float lifeSpan, float dmg);
	ProjectileManagerComponent * MakeProjectileManagerComponent(std::vector<shared_ptr<GameObject>> projectiles);
	
	AIAgentComponent * MakeAIAgentComponent(TransformComponent* trans, SpriteAnimatorComponent* anim, RigidBodyComponent* rb, DamageableComponent* dmg, ProjectileManagerComponent* proj, TransformComponent* cameraTransform, float patrolTime, AIAgentPatrolDirection patrolStartDir, float idleTime, TransformComponent* targetTransform, float viewRange, float shotInterval);
	
	GUITextValueComponent * MakeGUITextValueComponent(std::string valueName, int renderLayer, std::string text, float r, float g, float b, TransformComponent* transform, Vec2 offset);
	GUITextDamageComponent * MakeGUITextDamageComponent(DamageableComponent* dmg, int renderLayer, std::string text, float r, float g, float b, TransformComponent* transform, Vec2 offset);

	GameCameraComponent * MakeGameCameraComponent(TransformComponent* trans, TransformComponent* focusTrans, float focusWidth, float focusHeight, float leftBound, float rightBound, float topBound, float bottomBound);
}