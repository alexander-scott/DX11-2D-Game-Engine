#include "ColliderRendererComponent.h"



ColliderRendererComponent::ColliderRendererComponent()
{
	mType = "Collider Renderer";
}


ColliderRendererComponent::~ColliderRendererComponent()
{
}

void ColliderRendererComponent::SetCollider(ColliderComponent * collider)
{
	_collider = collider;
	_colliderType = collider->GetType();
}

void ColliderRendererComponent::Draw(ICamera* cam)
{
	switch (_colliderType)
	{
		case ColliderType::ePolygon:
			PolygonColliderComponent* col = reinterpret_cast<PolygonColliderComponent *>(_collider);
			for (int i = 0; i < col->VertexCount - 1; i++)
			{
				cam->DrawLine(GetTransform()->GetPosition() + col->Vertices[i], GetTransform()->GetPosition() + col->Vertices[i + 1]);
			}
			break;
	}
}
