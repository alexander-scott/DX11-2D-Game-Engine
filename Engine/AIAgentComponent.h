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
	AIAgentComponent(TransformComponent* trans, SpriteAnimatorComponent* anim,	RigidBodyComponent* rb, DamageableComponent* dmg, TransformComponent* cameraTransform);

	~AIAgentComponent();

	virtual void Update(float deltaTime) override;

	void SetupPatrolling(float patrolTime, AIAgentPatrolDirection startDir, float idleTime);
	void SetupShooting(ProjectileManagerComponent* projectileMan, TransformComponent* targetTransform, float range, float shotInterval);

private:
	void ShootAtPlayer(float deltaTime);
	void Patrol(float deltaTime);

	bool CanSeePlayer();

	void UpdateAnimation();

	TransformComponent*			mAgentTransform;
	SpriteAnimatorComponent*	mAgentAnimator;
	RigidBodyComponent*			mAgentRigidBody;
	DamageableComponent*		mAgentDamageable;

	TransformComponent*			mCameraTransform;

	AIAgentState				mCurrentState;

	// PATROLLING STUFFF
	float						mPatrolTime;
	float						mIdleTime;
	AIAgentPatrolDirection		mPatrolDirection;

	float						mCurrentPatrolTime;
	float						mCurrentIdleTime;

	// SHOOTING STUFFF
	ProjectileManagerComponent*	mAgentProjectiles;
	TransformComponent*			mTargetTransform;
	float						mViewRange;
	float						mShotIntervals;
	float						mCurrentShotTimer;
};