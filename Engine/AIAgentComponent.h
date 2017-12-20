#pragma once

#include "IComponent.h"
#include "IUpdateable.h"

#include "RigidBodyComponent.h"
#include "SpriteAnimatorComponent.h"
#include "DamageableComponent.h"

#include "ProjectileManager.h"
#include "Audio.h"

class AIAgentComponent : public IComponent, public IUpdateable
{
public:
	AIAgentComponent(TransformComponent* trans, SpriteAnimatorComponent* anim,	RigidBodyComponent* rb, DamageableComponent* dmg, 
		ProjectileManager* projectileMan, TransformComponent* cameraTransform, float patrolTime, AIAgentPatrolDirection startDir, float idleTime);

	~AIAgentComponent();

	virtual void Update(float deltaTime) override;

private:
	void ShootAtPlayer(float deltaTime);
	void Patrol(float deltaTime);

	bool CanSeePlayer();

	void UpdateAnimation();

	TransformComponent*			_agentTransform;
	SpriteAnimatorComponent*	_agentAnimator;
	RigidBodyComponent*			_agentRigidBody;
	DamageableComponent*		_agentDamageable;

	ProjectileManager*			_agentProjectiles;
	TransformComponent*			_cameraTransform;

	AIAgentState				_currentState;

	// PATROLLING STUFFF
	float						_patrolTime;
	float						_idleTime;
	AIAgentPatrolDirection		_patrolDirection;

	float						_currentPatrolTime;
	float						_currentIdleTime;

	// SHOOTING STUFFF
};