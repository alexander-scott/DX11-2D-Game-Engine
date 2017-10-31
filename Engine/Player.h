#pragma once

#include "GameObject.h"
#include "RigidBody.h"

using namespace DirectX;

class Player : public GameObject
{
public:
	void UpdateDirection(const XMFLOAT2 & dir);

	void Init(const std::string& fileName, const XMFLOAT2 &pos, const float& rot) override;
	void Update(float deltaTime) override;
	void Draw(Graphics& gfx) const override;

private:
	AnimationType iCurSequence = AnimationType::StandingDown;
	std::vector<Animation> animations;

	RigidBody* rigidBody;
};

