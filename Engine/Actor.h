#pragma once

#include "Graphics.h"

class Actor
{
public:
	void SetSprite(const std::string fileName) { _fileName = fileName; }
	void SetPosition(const XMFLOAT2 &pos) { _pos = pos; }

	void Draw(Graphics& gfx) const;

	virtual void Update(float deltaTime);

protected:
	XMFLOAT2				_pos;
	std::string				_fileName;
};