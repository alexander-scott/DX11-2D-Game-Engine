#include "Player.h"



Player::Player()
{
	TransformComponent* playerTransform = ComponentFactory::MakeTransform(Vec2(350, 75));
	std::vector<AnimationDesc> animDescs;
	animDescs.push_back(AnimationDesc(0, 4, 64, 64, 64, 64, 8, 0.16f)); // Walking
	animDescs.push_back(AnimationDesc(4, 8, 64, 64, 64, 64, 1, 0.16f)); // Standing

	playerAnimator = ComponentFactory::MakeSpriteAnimator("Images\\mage_walk.dds", playerTransform, animDescs, (int)AnimationType::StandingDown);
	playerRigidBody = ComponentFactory::MakeRigidbody(playerTransform);
	AddComponent(playerTransform);
	AddComponent(playerAnimator);
	AddComponent(playerRigidBody);
}


Player::~Player()
{
}

void Player::UpdateDir(Vec2 dir)
{
	if (dir.x > 0.0f)
	{
		playerRigidBody->ApplyForce(Vec2(-0.000001f, 0));
	}
	else if (dir.x < 0.0f)
	{
		playerRigidBody->ApplyForce(Vec2(0.000001f, 0));
	}

	if (dir.y < 0.0f)
	{
		playerRigidBody->ApplyForce(Vec2(0, 0.000001f));
	}
	else if (dir.y > 0.0f)
	{
		playerRigidBody->ApplyForce(Vec2(0, -0.000001f));
	}

	if (dir.x > 0.0f)
	{
		playerAnimator->UpdateAnimationSequence((int)AnimationType::WalkingRight);
	}
	else if (dir.x < 0.0f)
	{
		playerAnimator->UpdateAnimationSequence((int)AnimationType::WalkingLeft);
	}
	else if (dir.y < 0.0f)
	{
		playerAnimator->UpdateAnimationSequence((int)AnimationType::WalkingUp);
	}
	else if (dir.y > 0.0f)
	{
		playerAnimator->UpdateAnimationSequence((int)AnimationType::WalkingDown);
	}
	else 
	{
		if (playerRigidBody->GetVelocity().x > 0.1f)
		{
			playerAnimator->UpdateAnimationSequence((int)AnimationType::StandingRight);
		}
		else if (playerRigidBody->GetVelocity().x < -0.1f)
		{
			playerAnimator->UpdateAnimationSequence((int)AnimationType::StandingLeft);
		}
		else if (playerRigidBody->GetVelocity().y < -0.1f)
		{
			playerAnimator->UpdateAnimationSequence((int)AnimationType::StandingUp);
		}
		else if (playerRigidBody->GetVelocity().y > 0.1f)
		{
			playerAnimator->UpdateAnimationSequence((int)AnimationType::StandingDown);
		}
	}
}
