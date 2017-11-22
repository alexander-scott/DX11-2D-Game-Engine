#include "CircleColliderComponent.h"



CircleColliderComponent::CircleColliderComponent(TransformComponent* trans, RigidBodyComponent* rb)
{
	_type = "Circle Collider";

	_transformComponent = trans;
	_rigidyBodyComponent = rb;
}


CircleColliderComponent::~CircleColliderComponent()
{
}
