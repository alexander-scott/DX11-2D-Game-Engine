#pragma once

#include "Actor.h"

using namespace DirectX;

class Player : public Actor
{
public:
	using Actor::Actor;

	void UpdateDirection(const XMFLOAT2 & dir);

	void Update(float deltaTime) override;
	void Draw(Graphics& gfx) const override;

private:

	XMFLOAT2 vel = XMFLOAT2(0, 0);
	float speed = 110.0f;
};

