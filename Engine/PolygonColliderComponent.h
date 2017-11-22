#pragma once

#include "ColliderComponent.h"

#define MaxPolyVertexCount 64

class PolygonColliderComponent : public ColliderComponent
{
public:
	PolygonColliderComponent(TransformComponent* trans, RigidBodyComponent* rb);
	~PolygonColliderComponent();

	virtual ColliderType GetType(void) const override { return ColliderType::ePolygon; }

	void SetVerticies(Vec2 *vertices, int count);
	void SetBox(float hw, float hh);
	Vec2 GetSupport(const Vec2& dir);

	int m_vertexCount;
	Vec2 m_vertices[MaxPolyVertexCount];
	Vec2 m_normals[MaxPolyVertexCount];
};

