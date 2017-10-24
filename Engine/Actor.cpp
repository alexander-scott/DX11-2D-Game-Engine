#include "Actor.h"

Actor::Actor(const std::string& fileName, const XMFLOAT2 & pos) : _fileName(fileName), _pos(pos)
{
	for (int i = 0; i < (int)Sequence::StandingLeft; i++) // Add the walking animations - 9 frames
	{
		animations.emplace_back(Animation(90, 90 * i, 90, 90, 9, fileName, 0.16f));
	}
	for (int i = (int)Sequence::StandingLeft; i < (int)Sequence::Count; i++) // Add the standing animations - 1 frame
	{
		animations.emplace_back(Animation(0, 90 * (i - (int)Sequence::StandingLeft), 90, 90, 1, fileName, 0.16f));
	}
}

void Actor::Draw(Graphics& gfx) const
{
	gfx.DrawSpriteDX11(_fileName, _pos);
}

void Actor::Update(float deltaTime)
{
}
