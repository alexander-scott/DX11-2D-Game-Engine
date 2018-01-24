#pragma once

#include "ColliderComponent.h"

class PolygonColliderComponent : public ColliderComponent
{
public:
	PolygonColliderComponent(TransformComponent* trans, RigidBodyComponent* rb);
	~PolygonColliderComponent();

	virtual ColliderType GetType(void) const override { return ColliderType::ePolygon; }
	virtual void ComputeMass(float density) override;
	virtual Rect GetRect() override;

	virtual Vec2 GetCentre() override { return Vec2(mTransformComponent->GetWorldPosition().x + mHalfWidth, mTransformComponent->GetWorldPosition().y + mHalfHeight); }

	void SetVerticies(Vec2 *vertices, int count);
	Vec2 GetSupport(const Vec2& dir);

	int VertexCount;
	Vec2 Vertices[MAX_POLY_VERTEX_COUNT];
	Vec2 Normals[MAX_POLY_VERTEX_COUNT];

protected:	
	float				mHalfWidth;
	float				mHalfHeight;

private:
	Vec2				mCentre;
};

