#include "GameObject.h"

void GameObject::Init(const std::string& fileName, const XMFLOAT2 & pos, const float& rot)
{
	_fileName = fileName;
	_pos = pos;
	_rot = rot;
}

void GameObject::Draw(Graphics& gfx) const
{
	gfx.DrawSpriteDX11(_fileName, _pos, _rot);
}

void GameObject::Update(float deltaTime)
{
}
