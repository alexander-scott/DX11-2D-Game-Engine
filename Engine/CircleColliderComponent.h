#pragma once

#include "ColliderComponent.h"

class CircleColliderComponent : public ColliderComponent
{
public:
	CircleColliderComponent();
	~CircleColliderComponent();

	void SetRadius(float rad) { radius = rad; }
	float GetRadius() { return radius; }
	virtual ColliderType GetType(void) const override { return ColliderType::eCircle; }
};

