#include "Player.h"

void Player::Init(const std::string& fileName, const XMFLOAT2 & pos, const float& rot)
{
	GameObject::Init(fileName, pos, rot);

	for (int i = 0; i < (int)AnimationType::StandingUp; i++) // Add the walking animations - 9 frames
	{
		animations.emplace_back(Animation(64, 64 * i, 64, 64, 8, fileName, 0.16f));
	}
	for (int i = (int)AnimationType::StandingUp; i < (int)AnimationType::Count; i++) // Add the standing animations - 1 frame
	{
		animations.emplace_back(Animation(0, 64 * (i - (int)AnimationType::StandingUp), 64, 64, 1, fileName, 0.16f));
	}
}

void Player::UpdateDirection(const XMFLOAT2 &dir)
{
	if (dir.x > 0.0f)
	{
		iCurSequence = AnimationType::WalkingRight;
	}
	else if (dir.x < 0.0f)
	{
		iCurSequence = AnimationType::WalkingLeft;
	}
	else if (dir.y < 0.0f)
	{
		iCurSequence = AnimationType::WalkingUp;
	}
	else if (dir.y > 0.0f)
	{
		iCurSequence = AnimationType::WalkingDown;
	}
	else
	{
		if (vel.x > 0.0f)
		{
			iCurSequence = AnimationType::StandingRight;
		}
		else if (vel.x < 0.0f)
		{
			iCurSequence = AnimationType::StandingLeft;
		}
		else if (vel.y < 0.0f)
		{
			iCurSequence = AnimationType::StandingUp;
		}
		else if (vel.y > 0.0f)
		{
			iCurSequence = AnimationType::StandingDown;
		}
	}

	vel = XMFLOAT2(dir.x * speed, dir.y * speed);
}

void Player::Update(float deltaTime)
{
	_pos = XMFLOAT2(_pos.x + (vel.x * deltaTime), _pos.y + (vel.y * deltaTime));

	animations[(int)iCurSequence].Update(deltaTime);
}

void Player::Draw(Graphics & gfx) const
{
	animations[(int)iCurSequence].Draw(_pos, _rot, gfx);
}
