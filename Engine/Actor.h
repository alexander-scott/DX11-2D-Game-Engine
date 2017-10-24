#pragma once

#include "Graphics.h"
#include "Animation.h"
#include "Consts.h"

class Actor
{
public:
	virtual void Init(const std::string& fileName, const XMFLOAT2 &pos);
	virtual void Draw(Graphics& gfx) const;
	virtual void Update(float deltaTime);

protected:
	XMFLOAT2				_pos;
	std::string				_fileName;
};