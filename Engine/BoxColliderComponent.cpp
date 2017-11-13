#include "BoxColliderComponent.h"

BoxColliderComponent::BoxColliderComponent()
{
	_type = "Box Collider Component";
	colliderType = ColliderType::Square;
}

BoxColliderComponent::~BoxColliderComponent()
{
}

Collider BoxColliderComponent::ReturnCollider()
{
	return AABB(GetTransformComponent()->GetPosition(), _width, _height);
}
