#include "Actor.h"

void Actor::Init(const std::string& fileName, const XMFLOAT2 & pos)
{
	_fileName = fileName;
	_pos = pos;
}

void Actor::Draw(Graphics& gfx) const
{
	gfx.DrawSpriteDX11(_fileName, _pos);
}

void Actor::Update(float deltaTime)
{
}
