#include "Player.h"

void Player::UpdateDirection(const XMFLOAT2 &dir)
{
	vel = XMFLOAT2(dir.x * speed, dir.y * speed);
}

void Player::Update(float deltaTime)
{
	_pos = XMFLOAT2(_pos.x + (vel.x * deltaTime), _pos.y + (vel.y * deltaTime));
}

void Player::Draw(Graphics & gfx) const
{
	animations[(int)iCurSequence].Draw(_pos, gfx);
}
