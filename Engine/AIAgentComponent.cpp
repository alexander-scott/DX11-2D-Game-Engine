#include "AIAgentComponent.h"

#include "AddForceMessage.h"

AIAgentComponent::AIAgentComponent(TransformComponent * trans, SpriteAnimatorComponent * anim, RigidBodyComponent * rb, DamageableComponent * dmg, TransformComponent * cameraTransform)
	: mAgentTransform(trans), mAgentAnimator(anim), mAgentRigidBody(rb), mAgentDamageable(dmg), mCameraTransform(cameraTransform)
{
	mCurrentState = AIAgentState::ePatrolling;
}

AIAgentComponent::~AIAgentComponent()
{
}

void AIAgentComponent::Update(float deltaTime)
{
	switch (mCurrentState)
	{
		case AIAgentState::ePatrolling:
		{
			Patrol(deltaTime);
			UpdateAnimation();
			break;
		}

		case AIAgentState::eShooting:
		{
			ShootAtPlayer(deltaTime);
			break;
		}
	}
}

void AIAgentComponent::SetupPatrolling(float patrolTime, AIAgentPatrolDirection startDir, float idleTime)
{
	mCurrentPatrolTime = 0;
	mCurrentIdleTime = 0;

	mPatrolTime = patrolTime;
	mPatrolDirection = startDir;
	mIdleTime = idleTime;
}

void AIAgentComponent::SetupShooting(ProjectileManagerComponent * projectileMan, TransformComponent * targetTransform, float range, float shotInterval)
{
	mCurrentShotTimer = 0;
	mAgentProjectiles = projectileMan;
	mTargetTransform = targetTransform;
	mViewRange = range;
	mShotIntervals = shotInterval;
}

void AIAgentComponent::ShootAtPlayer(float deltaTime)
{
	UpdateAnimationSequenceMessage updateSeqMsg;
	if (mTargetTransform->GetPosition().x > mAgentTransform->GetPosition().x) // Face the player
		updateSeqMsg.SetSequence((int)AnimationType::StandingRight);
	else
		updateSeqMsg.SetSequence((int)AnimationType::StandingLeft);
	mAgentAnimator->RecieveMessage(updateSeqMsg);
	 
	if (mCurrentShotTimer > mShotIntervals)
	{
		mCurrentShotTimer = 0;

		auto go = mAgentProjectiles->GetGameObject("Player", AI_PROJECTILE_DAMAGE);
		Vec2 dir = mTargetTransform->GetPosition() - mAgentTransform->GetPosition();
		dir.Normalize();

		go->GetComponent<TransformComponent>()->SetPosition(mAgentTransform->GetPosition() + (dir * 10));
		go->GetComponent<RigidBodyComponent>()->ApplyForce(dir * AI_PROJECTILE_SPEED);

		Audio::Instance().PlaySoundEffect("GunShot");
	}
	else
	{
		mCurrentShotTimer += deltaTime;
	}

	Vec2 dir = Vec2(mTargetTransform->GetPosition().x - mAgentTransform->GetPosition().x, mTargetTransform->GetPosition().y - mAgentTransform->GetPosition().y);
	float distance = dir.Len();
	if (distance > mViewRange) // If player is too far away
	{
		mCurrentState = AIAgentState::ePatrolling;
	}
}

void AIAgentComponent::Patrol(float deltaTime)
{
	// If the agent has spent more time patrolling than initially specified, move to being idle
	if (mCurrentPatrolTime > mPatrolTime)
	{
		// If the agent has spent more time being idle than initially specified, restart the patrol in the opposite direction
		if (mCurrentIdleTime > mIdleTime)
		{
			mPatrolDirection = (mPatrolDirection == AIAgentPatrolDirection::ePatrollingLeft) ? AIAgentPatrolDirection::ePatrollingRight : AIAgentPatrolDirection::ePatrollingLeft;
			mCurrentPatrolTime = 0;
			mCurrentIdleTime = 0;
		}
		else 
		{
			mCurrentIdleTime += deltaTime;
		}
	}
	else
	{
		Vec2 dir = Vec2(0.0f, 0.0f);
		switch (mPatrolDirection)
		{
			case AIAgentPatrolDirection::ePatrollingLeft:
			{
				if (mAgentRigidBody->GetVelocity().x > -AI_LATERAL_MAX_SPEED)
				{
					dir.x -= 1;
				}
				break;
			}

			case AIAgentPatrolDirection::ePatrollingRight:
			{
				if (mAgentRigidBody->GetVelocity().x < AI_LATERAL_MAX_SPEED)
				{
					dir.x += 1;
				}
				break;
			}
		}

		AddForceMessage addForceMsg(dir);
		mAgentRigidBody->RecieveMessage(addForceMsg);

		mCurrentPatrolTime += deltaTime;
	}

	if (CanSeePlayer())
	{
		mCurrentState = AIAgentState::eShooting;
	}
}

bool AIAgentComponent::CanSeePlayer()
{
	if (mAgentRigidBody->GetVelocity().x > 0) // Moving right
	{
		if (mTargetTransform->GetPosition().x > mAgentTransform->GetPosition().x) // If the target is more right than the transform
		{
			// If the target is within view range
			Vec2 dir = Vec2(mTargetTransform->GetPosition().x - mAgentTransform->GetPosition().x, mTargetTransform->GetPosition().y - mAgentTransform->GetPosition().y);
			float distance = dir.Len();
			if (distance < mViewRange)
			{
				return true;
			}
		}
	}
	else
	{
		if (mTargetTransform->GetPosition().x < mAgentTransform->GetPosition().x) // If the target is more left than the transform
		{
			Vec2 dir = Vec2(mTargetTransform->GetPosition().x - mAgentTransform->GetPosition().x, mTargetTransform->GetPosition().y - mAgentTransform->GetPosition().y);
			float distance = dir.Len();
			if (distance < mViewRange)
			{
				return true;
			}
		}
	}

	return false;
}

void AIAgentComponent::UpdateAnimation()
{
	float downVal = (mAgentRigidBody->GetVelocity().y > 0) ? mAgentRigidBody->GetVelocity().y : 0;
	float upVal = (mAgentRigidBody->GetVelocity().y < 0) ? (mAgentRigidBody->GetVelocity().y * -1) : 0;
	float leftVal = (mAgentRigidBody->GetVelocity().x < 0) ? (mAgentRigidBody->GetVelocity().x * -1) : 0;
	float rightVal = (mAgentRigidBody->GetVelocity().x > 0) ? mAgentRigidBody->GetVelocity().x : 0;

	UpdateAnimationSequenceMessage updateSeqMsg;

	if (downVal > upVal && downVal > leftVal && downVal > rightVal)
	{
		if (downVal < 5)
		{
			updateSeqMsg.SetSequence((int)AnimationType::StandingDown);
		}
		else
		{
			updateSeqMsg.SetSequence((int)AnimationType::WalkingDown);
		}
	}
	else if (upVal > downVal && upVal > leftVal && upVal > rightVal)
	{
		if (upVal < 5)
		{
			updateSeqMsg.SetSequence((int)AnimationType::StandingUp);
		}
		else
		{
			updateSeqMsg.SetSequence((int)AnimationType::WalkingUp);
		}
	}
	else if (leftVal > downVal && leftVal > upVal && leftVal > rightVal)
	{
		if (leftVal < 5)
		{
			updateSeqMsg.SetSequence((int)AnimationType::StandingLeft);
		}
		else
		{
			updateSeqMsg.SetSequence((int)AnimationType::WalkingLeft);
		}
	}
	else if (rightVal > downVal && rightVal > upVal && rightVal > leftVal)
	{
		if (rightVal < 5)
		{
			updateSeqMsg.SetSequence((int)AnimationType::StandingRight);
		}
		else
		{
			updateSeqMsg.SetSequence((int)AnimationType::WalkingRight);
		}
	}

	mAgentAnimator->RecieveMessage(updateSeqMsg);
}
