#include "BoxColliderComponent.h"



BoxColliderComponent::BoxColliderComponent(TransformComponent* trans, RigidBodyComponent* rb) : PolygonColliderComponent(trans, rb)
{
}


BoxColliderComponent::~BoxColliderComponent()
{
}
