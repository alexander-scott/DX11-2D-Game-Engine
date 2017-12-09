#include "BoxColliderComponent.h"



BoxColliderComponent::BoxColliderComponent(TransformComponent* trans, RigidBodyComponent* rb) : PolygonColliderComponent(trans, rb)
{
}


BoxColliderComponent::~BoxColliderComponent()
{
}

void BoxColliderComponent::SetBox(float hw, float hh)
{
	_halfWidth = hw; _halfHeight = hh;

	m_vertexCount = 4;
	m_vertices[0].Set(-hw, -hh);
	m_vertices[1].Set(hw, -hh);
	m_vertices[2].Set(hw, hh);
	m_vertices[3].Set(-hw, hh);
	m_normals[0].Set(0.0f, -1.0f);
	m_normals[1].Set(1.0f, 0.0f);
	m_normals[2].Set(0.0f, 1.0f);
	m_normals[3].Set(-1.0f, 0.0f);
}
