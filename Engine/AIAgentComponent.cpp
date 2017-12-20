#include "AIAgentComponent.h"

#include "AddForceMessage.h"

AIAgentComponent::AIAgentComponent(TransformComponent * trans, SpriteAnimatorComponent * anim, RigidBodyComponent * rb, DamageableComponent * dmg,	ProjectileManager * projectileMan, TransformComponent * cameraTransform, float patrolTime, AIAgentPatrolDirection startDir, float idleTime)
	: _agentTransform(trans), _agentAnimator(anim), _agentRigidBody(rb), _agentDamageable(dmg), _agentProjectiles(projectileMan), _cameraTransform(cameraTransform), _patrolTime(patrolTime), _idleTime(idleTime)
{
	_currentPatrolTime = 0;
	_currentIdleTime = 0;
	_patrolDirection = startDir;
	_currentState = AIAgentState::ePatrolling;
}

AIAgentComponent::~AIAgentComponent()
{
}

void AIAgentComponent::Update(float deltaTime)
{
	switch (_currentState)
	{
		case AIAgentState::ePatrolling:
		{
			Patrol(deltaTime);
			break;
		}

		case AIAgentState::eShooting:
		{

			break;
		}
	}

	UpdateAnimation();
}

void AIAgentComponent::ShootAtPlayer(float deltaTime)
{

}

void AIAgentComponent::Patrol(float deltaTime)
{
	// If the agent has spent more time patrolling than initially specified, move to being idle
	if (_currentPatrolTime > _patrolTime)
	{
		// If the agent has spent more time being idle than initially specified, restart the patrol in the opposite direction
		if (_currentIdleTime > _idleTime)
		{
			_patrolDirection = (_patrolDirection == AIAgentPatrolDirection::ePatrollingLeft) ? AIAgentPatrolDirection::ePatrollingRight : AIAgentPatrolDirection::ePatrollingLeft;
			_currentPatrolTime = 0;
			_currentIdleTime = 0;
		}
		else 
		{
			_currentIdleTime += deltaTime;
		}
	}
	else
	{
		Vec2 dir = Vec2(0.0f, 0.0f);
		switch (_patrolDirection)
		{
			case AIAgentPatrolDirection::ePatrollingLeft:
			{
				if (_agentRigidBody->GetVelocity().x > -AI_LATERAL_MAX_SPEED)
				{
					dir.x -= 1;
				}
				break;
			}

			case AIAgentPatrolDirection::ePatrollingRight:
			{
				if (_agentRigidBody->GetVelocity().x < AI_LATERAL_MAX_SPEED)
				{
					dir.x += 1;
				}
				break;
			}
		}

		AddForceMessage addForceMsg;
		addForceMsg.SetForce(dir);
		_agentRigidBody->RecieveMessage(addForceMsg);

		_currentPatrolTime += deltaTime;
	}

	if (CanSeePlayer())
	{
		_currentState = AIAgentState::eShooting;
	}
}

bool AIAgentComponent::CanSeePlayer()
{
	return false;
}

void AIAgentComponent::UpdateAnimation()
{
	float downVal = (_agentRigidBody->GetVelocity().y > 0) ? _agentRigidBody->GetVelocity().y : 0;
	float upVal = (_agentRigidBody->GetVelocity().y < 0) ? (_agentRigidBody->GetVelocity().y * -1) : 0;
	float leftVal = (_agentRigidBody->GetVelocity().x < 0) ? (_agentRigidBody->GetVelocity().x * -1) : 0;
	float rightVal = (_agentRigidBody->GetVelocity().x > 0) ? _agentRigidBody->GetVelocity().x : 0;

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

	_agentAnimator->RecieveMessage(updateSeqMsg);
}
