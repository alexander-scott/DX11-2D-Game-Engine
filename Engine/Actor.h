#pragma once

#include "Graphics.h"
#include "Animation.h"
#include "Consts.h"

class Actor
{
public:
	explicit Actor(const std::string& fileName, const XMFLOAT2 &pos);

	void SetSprite(const std::string fileName) { _fileName = fileName; }
	void SetPosition(const XMFLOAT2 &pos) { _pos = pos; }

	virtual void Draw(Graphics& gfx) const;

	virtual void Update(float deltaTime);

protected:
	XMFLOAT2				_pos;
	std::string				_fileName;

	Sequence iCurSequence = Sequence::StandingDown;
	std::vector<Animation> animations;
};