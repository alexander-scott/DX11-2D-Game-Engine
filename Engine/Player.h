#pragma once

#include "Actor.h"

using namespace DirectX;

class Player : public Actor
{
public:
	void UpdateDirection(const XMFLOAT2 & dir);

	void Init(const std::string& fileName, const XMFLOAT2 &pos) override;
	void Update(float deltaTime) override;
	void Draw(Graphics& gfx) const override;

private:
	Sequence iCurSequence = Sequence::StandingDown;
	std::vector<Animation> animations;

	XMFLOAT2 vel = XMFLOAT2(0, 0);
	float speed = 110.0f;
};

