#include "Actor.h"

void Actor::Draw(Graphics& gfx) const
{
	gfx.DrawSpriteDX11(_fileName, _pos);
}

void Actor::Update(float deltaTime)
{
}
