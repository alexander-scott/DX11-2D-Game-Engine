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

void Player::Update(float deltaTime)
{
	GameObject::Update(deltaTime);

	float downVal = (playerRigidBody->GetVelocity().y > 0) ? playerRigidBody->GetVelocity().y : 0;
	float upVal = (playerRigidBody->GetVelocity().y < 0) ? (playerRigidBody->GetVelocity().y * -1) : 0;
	float leftVal = (playerRigidBody->GetVelocity().x < 0) ? (playerRigidBody->GetVelocity().x * -1) : 0;
	float rightVal = (playerRigidBody->GetVelocity().x > 0) ? playerRigidBody->GetVelocity().x : 0;

	if (downVal > upVal && downVal > leftVal && downVal > rightVal)
	{
		if (downVal < 10)
			playerAnimator->UpdateAnimationSequence((int)AnimationType::StandingDown);
		else
			playerAnimator->UpdateAnimationSequence((int)AnimationType::WalkingDown);
	}
	else if (upVal > downVal && upVal > leftVal && upVal > rightVal)
	{
		if (upVal < 10)
			playerAnimator->UpdateAnimationSequence((int)AnimationType::StandingUp);
		else
			playerAnimator->UpdateAnimationSequence((int)AnimationType::WalkingUp);
	}
	else if (leftVal > downVal && leftVal > upVal && leftVal > rightVal)
	{
		if (leftVal < 10)
			playerAnimator->UpdateAnimationSequence((int)AnimationType::StandingLeft);
		else
			playerAnimator->UpdateAnimationSequence((int)AnimationType::WalkingLeft);
	}
	else if (rightVal > downVal && rightVal > upVal && rightVal > leftVal)
	{
		if (rightVal < 10)
			playerAnimator->UpdateAnimationSequence((int)AnimationType::StandingRight);
		else
			playerAnimator->UpdateAnimationSequence((int)AnimationType::WalkingRight);
	}
}
