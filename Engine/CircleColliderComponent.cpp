#include "CircleColliderComponent.h"



CircleColliderComponent::CircleColliderComponent(TransformComponent* trans, RigidBodyComponent* rb)
{
	mType = "Circle Collider";

	mTransformComponent = trans;
	mRigidyBodyComponent = rb;
}


CircleColliderComponent::~CircleColliderComponent()
{
}

void CircleColliderComponent::ComputeMass(float density)
{
	if (mRigidyBodyComponent->GetInverseMass() == 0)
		return;

	mRigidyBodyComponent->SetMass(PI * mRadius * mRadius * density);
	mRigidyBodyComponent->SetInverseMass((mRigidyBodyComponent->GetMass()) ? 1.0f / mRigidyBodyComponent->GetMass() : 0.0f);
	mRigidyBodyComponent->SetIntertia(mRigidyBodyComponent->GetMass() * mRadius * mRadius);
	mRigidyBodyComponent->SetInverseIntertia((mRigidyBodyComponent->GetIntertia()) ? 1.0f / mRigidyBodyComponent->GetIntertia() : 0.0f);
}

Rect CircleColliderComponent::GetRect()
{
	Vec2 pos = mTransformComponent->GetPosition();
	Rect r;
	r.LeftX = (int)pos.x;
	r.TopY = (int)pos.y;
	r.RightX = (int)pos.x + (int)mRadius;
	r.BotY = (int)pos.y + (int)mRadius;
	r.Centre = Vec2(pos.x + (mRadius / 2), pos.y + (mRadius / 2));

	return r;
}