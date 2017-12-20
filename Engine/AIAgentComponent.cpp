#include "AIAgentComponent.h"

#include "AddForceMessage.h"

AIAgentComponent::AIAgentComponent(TransformComponent * trans, SpriteAnimatorComponent * anim, RigidBodyComponent * rb, DamageableComponent * dmg,	ProjectileManager * projectileMan, TransformComponent * cameraTransform)
	: _agentTransform(trans), _agentAnimator(anim), _agentRigidBody(rb), _agentDamageable(dmg), _agentProjectiles(projectileMan), _cameraTransform(cameraTransform)
{
	_currentPatrolTime = 0;
	_currentIdleTime = 0;
	_currentState = AIAgentState::eShooting;
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

			break;
		}

		case AIAgentState::eShooting:
		{

			break;
		}
	}
}

void AIAgentComponent::RecieveMessage(IMessage & message)
{
}

void AIAgentComponent::ShootAtPlayer()
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
				if (_agentRigidBody->GetVelocity().x < PLAYER_LATERAL_MAX_SPEED)
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
