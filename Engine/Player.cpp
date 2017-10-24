#include "Player.h"

void Player::Init(const std::string& fileName, const XMFLOAT2 & pos)
{
	_fileName = fileName;
	_pos = pos;

	for (int i = 0; i < (int)Sequence::StandingUp; i++) // Add the walking animations - 9 frames
	{
		animations.emplace_back(Animation(64, 64 * i, 64, 64, 9, fileName, 0.16f));
	}
	for (int i = (int)Sequence::StandingUp; i < (int)Sequence::Count; i++) // Add the standing animations - 1 frame
	{
		animations.emplace_back(Animation(0, 64 * (i - (int)Sequence::StandingUp), 64, 64, 1, fileName, 0.16f));
	}
}

void Player::UpdateDirection(const XMFLOAT2 &dir)
{
	if (dir.x > 0.0f)
	{
		iCurSequence = Sequence::WalkingRight;
	}
	else if (dir.x < 0.0f)
	{
		iCurSequence = Sequence::WalkingLeft;
	}
	else if (dir.y < 0.0f)
	{
		iCurSequence = Sequence::WalkingUp;
	}
	else if (dir.y > 0.0f)
	{
		iCurSequence = Sequence::WalkingDown;
	}
	else
	{
		if (vel.x > 0.0f)
		{
			iCurSequence = Sequence::StandingRight;
		}
		else if (vel.x < 0.0f)
		{
			iCurSequence = Sequence::StandingLeft;
		}
		else if (vel.y < 0.0f)
		{
			iCurSequence = Sequence::StandingUp;
		}
		else if (vel.y > 0.0f)
		{
			iCurSequence = Sequence::StandingDown;
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
	animations[(int)iCurSequence].Draw(_pos, gfx);
}
