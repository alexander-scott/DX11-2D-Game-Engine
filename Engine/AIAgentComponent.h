#pragma once

#include "IComponent.h"
#include "IUpdateable.h"

#include "RigidBodyComponent.h"
#include "SpriteAnimatorComponent.h"
#include "DamageableComponent.h"

#include "ProjectileManagerComponent.h"
#include "Audio.h"

class AIAgentComponent : public IComponent, public IUpdateable
{
public:
	AIAgentComponent(TransformComponent* trans, SpriteAnimatorComponent* anim,	RigidBodyComponent* rb, DamageableComponent* dmg, 
		ProjectileManagerComponent* projectileMan, TransformComponent* cameraTransform, float patrolTime, AIAgentPatrolDirection startDir, float idleTime);

	~AIAgentComponent();

	virtual void Update(float deltaTime) override;

private:
	void ShootAtPlayer(float deltaTime);
	void Patrol(float deltaTime);

	bool CanSeePlayer();

	void UpdateAnimation();

	TransformComponent*			mAgentTransform;
	SpriteAnimatorComponent*	mAgentAnimator;
	RigidBodyComponent*			mAgentRigidBody;
	DamageableComponent*		mAgentDamageable;

	ProjectileManagerComponent*	mAgentProjectiles;
	TransformComponent*			mCameraTransform;

	AIAgentState				mCurrentState;

	// PATROLLING STUFFF
	float						mPatrolTime;
	float						mIdleTime;
	AIAgentPatrolDirection		mPatrolDirection;

	float						mCurrentPatrolTime;
	float						mCurrentIdleTime;

	// SHOOTING STUFFF
};