#include "Player.h"

Player::Player()
{
	// TRANSFORM COMPONENT
	TransformComponent* playerTransform = ComponentFactory::MakeTransform(Vec2(350, 150), 0, 1);
	AddComponent(playerTransform);

	// RIGIDBODY COMPONENT
	playerRigidBody = ComponentFactory::MakeRigidbody(false); // Cache the rigidbody
	AddComponent(playerRigidBody);

	// CIRCLE COLLIDER COMPONENT
	AddComponent(ComponentFactory::MakeCircleCollider(30, playerTransform, playerRigidBody));

	// SPRITE ANIMATOR COMPONENT
	std::vector<AnimationDesc> animDescs;
	animDescs.push_back(AnimationDesc(0, 4, 64, 64, 64, 64, 8, 0.16f)); // Walking
	animDescs.push_back(AnimationDesc(4, 8, 0, 64, 64, 64, 1, 0.16f)); // Standing
	AddComponent(ComponentFactory::MakeSpriteAnimator(SpriteName::MageWalk, playerTransform, animDescs, (int)AnimationType::StandingDown));
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	GameObject::Update(deltaTime);

	CheckInput();
	UpdateAnimation();
}

void Player::UpdateAnimation()
{
	float downVal = (playerRigidBody->GetVelocity().y > 0) ? playerRigidBody->GetVelocity().y : 0;
	float upVal = (playerRigidBody->GetVelocity().y < 0) ? (playerRigidBody->GetVelocity().y * -1) : 0;
	float leftVal = (playerRigidBody->GetVelocity().x < 0) ? (playerRigidBody->GetVelocity().x * -1) : 0;
	float rightVal = (playerRigidBody->GetVelocity().x > 0) ? playerRigidBody->GetVelocity().x : 0;

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

	SendMessageToComponents(updateSeqMsg);
}

void Player::CheckInput()
{
	Vec2 dir = Vec2(0.0f, 0.0f);
	if (Keyboard::Instance().KeyIsPressed(VK_SPACE))
	{
		dir.y += 0.00001f;
	}
	if (Keyboard::Instance().KeyIsPressed(VK_LEFT))
	{
		dir.x += 0.00001f;
	}
	if (Keyboard::Instance().KeyIsPressed(VK_RIGHT))
	{
		dir.x -= 0.00001f;
	}

	// Move the player in the specified direction
	if (dir.x != 0 || dir.y != 0)
	{
		AddForceMessage addForceMsg;
		addForceMsg.SetForce(dir);
		SendMessageToComponents(addForceMsg);
	}
}
