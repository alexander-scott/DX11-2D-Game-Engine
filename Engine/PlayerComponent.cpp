#include "PlayerComponent.h"

#include "UpdateAnimationSequenceMessage.h"
#include "AddForceMessage.h"
#include "CollisionMessage.h"

PlayerComponent::PlayerComponent(TransformComponent* trans, SpriteAnimatorComponent* anim, 
	RigidBodyComponent* rb, DamageableComponent* dmg, ProjectileManagerComponent* projectileMan, TransformComponent* cameraTransform)
	: mPlayerTransform(trans), mPlayerAnimator(anim), mPlayerRigidBody(rb), mPlayerDamageable(dmg), mPlayerProjectiles(projectileMan), mCameraTransform(cameraTransform)
{
	mIsGrounded = false;
	mCanJump = false;
	mIsShooting = false;
}


PlayerComponent::~PlayerComponent()
{
}

void PlayerComponent::Update(float deltaTime)
{
	if (!mPlayerDamageable->IsDead())
	{
		CheckInput();
		UpdateAnimation();

		mIsGrounded = false;
	}
	else 
	{
		throw;
	}
}

void PlayerComponent::RecieveMessage(IMessage & message)
{
	switch (message.GetType())
	{
		case MessageType::eCollision:
			CollisionMessage& colMsg = static_cast<CollisionMessage &> (message);
			if (colMsg.CollidedObject->GetTag() == "Tile")
			{
				TransformComponent* tileTrans = colMsg.CollidedObject->GetComponent<TransformComponent>();

				// Check if the tile we have collided with is directly beneath us aka we're standing on it. And make sure it's not a tile that is touching our sides
				if (tileTrans->GetPosition().y > mPlayerTransform->GetPosition().y &&
					!(tileTrans->GetPosition().x <= mPlayerTransform->GetPosition().x - 32 || 
						tileTrans->GetPosition().x >= mPlayerTransform->GetPosition().x + 32))
				{
					// If it is then we are on the ground
					mIsGrounded = true;
				}
			}

			break;
	}
}

void PlayerComponent::UpdateAnimation()
{
	float downVal = (mPlayerRigidBody->GetVelocity().y > 0) ? mPlayerRigidBody->GetVelocity().y : 0;
	float upVal = (mPlayerRigidBody->GetVelocity().y < 0) ? (mPlayerRigidBody->GetVelocity().y * -1) : 0;
	float leftVal = (mPlayerRigidBody->GetVelocity().x < 0) ? (mPlayerRigidBody->GetVelocity().x * -1) : 0;
	float rightVal = (mPlayerRigidBody->GetVelocity().x > 0) ? mPlayerRigidBody->GetVelocity().x : 0;

	UpdateAnimationSequenceMessage updateSeqMsg;
	if (downVal < 10 && upVal < 10 && leftVal < 10 && rightVal < 10)
		updateSeqMsg.SetSequence((int)AnimationType::StandingDown);
	else if (downVal > upVal && downVal > leftVal && downVal > rightVal)
		updateSeqMsg.SetSequence((int)AnimationType::StandingDown);
	else if (upVal > downVal && upVal > leftVal && upVal > rightVal)
		updateSeqMsg.SetSequence((int)AnimationType::WalkingUp);
	else if (leftVal > downVal && leftVal > upVal && leftVal > rightVal)
		updateSeqMsg.SetSequence((int)AnimationType::WalkingLeft);
	else if (rightVal > downVal && rightVal > upVal && rightVal > leftVal)
		updateSeqMsg.SetSequence((int)AnimationType::WalkingRight);

	mPlayerAnimator->RecieveMessage(updateSeqMsg);
}

void PlayerComponent::CheckInput()
{
	Vec2 dir = Vec2(0.0f, 0.0f);

	// If the player is on the ground they are allowed to jump. The player cannot hold down jump however, they must release the space bar before jumping again
	if (Keyboard::Instance().KeyIsPressed(VK_SPACE) && mIsGrounded && mCanJump)
	{
		mCanJump = false;
		dir.y -= 20;
		Audio::Instance().PlaySoundEffect("Jump");
	}
	else if (!Keyboard::Instance().KeyIsPressed(VK_SPACE))
	{
		mCanJump = true;
	}

	if (Keyboard::Instance().KeyIsPressed(VK_LEFT))
	{
		if (mPlayerRigidBody->GetVelocity().x > -PLAYER_LATERAL_MAX_SPEED)
		{
			dir.x -= 1;
		}
	}
	if (Keyboard::Instance().KeyIsPressed(VK_RIGHT))
	{
		if (mPlayerRigidBody->GetVelocity().x < PLAYER_LATERAL_MAX_SPEED)
		{
			dir.x += 1;
		}
	}

	// Move the player in the specified direction
	if (dir.x != 0 || dir.y != 0)
	{
		AddForceMessage addForceMsg(dir);
		mPlayerRigidBody->RecieveMessage(addForceMsg);
	}

	if (Mouse::Instance().LeftIsPressed())
	{
		if (!mIsShooting)
		{
			mIsShooting = true;
			ShootProjectile();
		}
	}
	else
	{
		mIsShooting = false;
	}
}

void PlayerComponent::ShootProjectile()
{
	GameObject* go = mPlayerProjectiles->GetGameObject("Enemy", PLAYER_PROJECTILE_DAMAGE);
	Vec2 spawnPos = Vec2(Mouse::Instance().GetPosX() + mCameraTransform->GetPosition().x, Mouse::Instance().GetPosY() + mCameraTransform->GetPosition().y);
	Vec2 dir = spawnPos - mPlayerTransform->GetPosition();
	dir.Normalize();

	go->GetComponent<TransformComponent>()->SetPosition(mPlayerTransform->GetPosition() + (dir * 5));
	go->GetComponent<RigidBodyComponent>()->SetVelocity(Vec2(0, 0));
	go->GetComponent<RigidBodyComponent>()->ApplyForce(dir * PLAYER_PROJECTILE_SPEED);
	mPlayerRigidBody->ApplyForce(-dir * PLAYER_SHOOT_KNOCKBACK);

	Audio::Instance().PlaySoundEffect("GunShot");
}
