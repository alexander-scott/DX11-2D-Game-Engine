#pragma once

#include "PolygonColliderComponent.h"

class BoxColliderComponent : public PolygonColliderComponent
{
public:
	BoxColliderComponent(TransformComponent* trans, RigidBodyComponent* rb);
	~BoxColliderComponent();
};

