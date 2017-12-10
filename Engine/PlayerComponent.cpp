#include "PlayerComponent.h"

#include "UpdateAnimationSequenceMessage.h"
#include "AddForceMessage.h"

PlayerComponent::PlayerComponent(SpriteAnimatorComponent* anim, RigidBodyComponent* rb) : _playerAnimator(anim), _playerRigidBody(rb)
{
}


PlayerComponent::~PlayerComponent()
{
}

void PlayerComponent::Update(float deltaTime)
{
	CheckInput();
	UpdateAnimation();	
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
	if (Keyboard::Instance().KeyIsPressed(VK_SPACE) && _playerRigidBody->GetGrounded())
	{
		dir.y -= 12;
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
}
