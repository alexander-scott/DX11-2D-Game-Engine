#include "ColliderRendererComponent.h"



ColliderRendererComponent::ColliderRendererComponent()
{
	_type = "Collider Renderer";
}


ColliderRendererComponent::~ColliderRendererComponent()
{
}

void ColliderRendererComponent::SetCollider(ColliderComponent * collider)
{
	_collider = collider;
	_colliderType = collider->GetType();
}

void ColliderRendererComponent::Draw(Graphics & gfx)
{
	switch (_colliderType)
	{
		case ColliderType::ePolygon:
			PolygonColliderComponent* col = reinterpret_cast<PolygonColliderComponent *>(_collider);
			for (int i = 0; i < col->m_vertexCount - 1; i++)
			{
				gfx.DrawLineDX11(GetTransform()->GetPosition() + col->m_vertices[i], GetTransform()->GetPosition() + col->m_vertices[i + 1]);
			}
			break;
	}
}
