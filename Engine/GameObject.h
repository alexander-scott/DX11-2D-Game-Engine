#pragma once

#include "Graphics.h"
#include "Animation.h"
#include "Consts.h"

class GameObject
{
public:
	virtual void Init(const std::string& fileName, const XMFLOAT2 &pos, const float& rot);

	virtual void Draw(Graphics& gfx) const;
	virtual void Update(float deltaTime);

protected:
	XMFLOAT2				_pos;
	float					_rot;
	std::string				_fileName;
};