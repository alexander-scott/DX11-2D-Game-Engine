#pragma once

#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "RigidBodyComponent.h"

class CircleColliderComponent : public ColliderComponent
{
public:
	CircleColliderComponent(TransformComponent* trans, RigidBodyComponent* rb);
	~CircleColliderComponent();

	void SetRadius(float rad) { radius = rad; }
	float GetRadius() { return radius; }

	virtual ColliderType GetType(void) const override { return ColliderType::eCircle; }
	virtual void ComputeMass(float density) override;
	virtual Rect GetRect() override;

	float radius;
};

