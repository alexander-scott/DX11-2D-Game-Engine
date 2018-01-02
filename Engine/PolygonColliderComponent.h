#pragma once

#include "ColliderComponent.h"

#define MaxPolyVertexCount 64

class PolygonColliderComponent : public ColliderComponent
{
public:
	PolygonColliderComponent(TransformComponent* trans, RigidBodyComponent* rb);
	~PolygonColliderComponent();

	virtual ColliderType GetType(void) const override { return ColliderType::ePolygon; }
	virtual void ComputeMass(float density) override;
	virtual Rect GetRect() override;
	virtual Rect GetPreviousRect() override;

	void SetVerticies(Vec2 *vertices, int count);
	Vec2 GetSupport(const Vec2& dir);

	int m_vertexCount;
	Vec2 m_vertices[MaxPolyVertexCount];
	Vec2 m_normals[MaxPolyVertexCount];

	virtual Vec2 GetCentre() override { return Vec2(_transformComponent->GetPosition().x + _halfWidth, _transformComponent->GetPosition().y + _halfHeight); }

protected:	
	float				_halfWidth;
	float				_halfHeight;

private:
	Vec2				_centre;
};

