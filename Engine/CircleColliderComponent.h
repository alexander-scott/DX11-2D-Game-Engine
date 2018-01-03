#pragma once

#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "RigidBodyComponent.h"

class CircleColliderComponent : public ColliderComponent
{
public:
	CircleColliderComponent(TransformComponent* trans, RigidBodyComponent* rb);
	~CircleColliderComponent();

	void SetRadius(float rad) { mRadius = rad; }
	float GetRadius() { return mRadius; }

	virtual ColliderType GetType(void) const override { return ColliderType::eCircle; }
	virtual void ComputeMass(float density) override;
	virtual Rect GetRect() override;

	virtual Vec2 GetCentre() override { return Vec2(mTransformComponent->GetPosition().x + (mRadius/2), mTransformComponent->GetPosition().y + (mRadius / 2)); }

private:
	float mRadius;
};

