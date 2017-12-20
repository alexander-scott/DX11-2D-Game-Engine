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

void CircleColliderComponent::ComputeMass(float density)
{
	if (_rigidyBodyComponent->GetInverseMass() == 0)
		return;

	_rigidyBodyComponent->SetMass(PI * radius * radius * density);
	_rigidyBodyComponent->SetInverseMass((_rigidyBodyComponent->GetMass()) ? 1.0f / _rigidyBodyComponent->GetMass() : 0.0f);
	_rigidyBodyComponent->SetIntertia(_rigidyBodyComponent->GetMass() * radius * radius);
	_rigidyBodyComponent->SetInverseIntertia((_rigidyBodyComponent->GetIntertia()) ? 1.0f / _rigidyBodyComponent->GetIntertia() : 0.0f);
}
