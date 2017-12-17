#include "PlayerComponent.h"

#include "UpdateAnimationSequenceMessage.h"
#include "AddForceMessage.h"
#include "CollisionMessage.h"

PlayerComponent::PlayerComponent(TransformComponent* trans, SpriteAnimatorComponent* anim, RigidBodyComponent* rb, DamageableComponent* dmg, ProjectileManager* projectileMan)
	: _playerTransform(trans), _playerAnimator(anim), _playerRigidBody(rb), _playerDamageable(dmg), _playerProjectiles(projectileMan)
{
	_grounded = false;
	_isShooting = false;
}


PlayerComponent::~PlayerComponent()
{
}

void PlayerComponent::Update(float deltaTime)
{
	if (!_playerDamageable->IsDead())
	{
		CheckInput();
		UpdateAnimation();

		_grounded = false;
	}
}

void PlayerComponent::RecieveMessage(IMessage & message)
{
	switch (message.GetType())
	{
		case MessageType::eCollision:
			CollisionMessage& colMsg = static_cast<CollisionMessage &> (message);
			if (colMsg.collidedObject->GetTag() == "Tile")
			{
				TransformComponent* tileTrans = colMsg.collidedObject->GetComponent<TransformComponent>();

				// Check if the tile we have collided with is directly beneath us aka we're standing on it. And make sure it's not a tile that is touching our sides
				if (tileTrans->GetPosition().y > _playerTransform->GetPosition().y &&
					!(tileTrans->GetPosition().x <= _playerTransform->GetPosition().x - 32 || 
						tileTrans->GetPosition().x >= _playerTransform->GetPosition().x + 32))
				{
					// If it is then we are on the ground
					_grounded = true;
				}
			}

			break;
	}
}

void PlayerComponent::UpdateAnimation()
{
	float downVal = (_playerRigidBody->GetVelocity().y > 0) ? _playerRigidBody->GetVelocity().y : 0;
	float upVal = (_playerRigidBody->GetVelocity().y < 0) ? (_playerRigidBody->GetVelocity().y * -1) : 0;
	float leftVal = (_playerRigidBody->GetVelocity().x < 0) ? (_playerRigidBody->GetVelocity().x * -1) : 0;
	float rightVal = (_playerRigidBody->GetVelocity().x > 0) ? _playerRigidBody->GetVelocity().x : 0;

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

	_playerAnimator->RecieveMessage(updateSeqMsg);
}

void PlayerComponent::CheckInput()
{
	Vec2 dir = Vec2(0.0f, 0.0f);
	if (Keyboard::Instance().KeyIsPressed(VK_SPACE) && _grounded)
	{
		dir.y -= 10;
	}
	if (Keyboard::Instance().KeyIsPressed(VK_LEFT))
	{
		dir.x -= 1;
	}
	if (Keyboard::Instance().KeyIsPressed(VK_RIGHT))
	{
		dir.x += 1;
	}

	// Move the player in the specified direction
	if (dir.x != 0 || dir.y != 0)
	{
		AddForceMessage addForceMsg;
		addForceMsg.SetForce(dir);
		_playerRigidBody->RecieveMessage(addForceMsg);
	}

	if (Mouse::Instance().LeftIsPressed())
	{
		if (!_isShooting)
		{
			_isShooting = true;
			ShootProjectile();
		}
	}
	else
	{
		_isShooting = false;
	}
}

void PlayerComponent::ShootProjectile()
{
	GameObject* go = _playerProjectiles->GetGameObject();
	go->GetComponent<TransformComponent>()->SetPosition(Vec2(_playerTransform->GetPosition().x, _playerTransform->GetPosition().y - 600));
}
