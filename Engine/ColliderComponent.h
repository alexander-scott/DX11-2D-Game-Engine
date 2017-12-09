#pragma once

#include "IComponent.h"

#include "Consts.h"
#include "TransformComponent.h"
#include "RigidBodyComponent.h"

class ColliderComponent : public IComponent
{
public:
	RigidBodyComponent* GetRigidbodyComponent() { return _rigidyBodyComponent; }
	TransformComponent* GetTransformComponent() { return _transformComponent; }

	virtual ColliderType GetType(void) const = 0;
	virtual void ComputeMass(float density) = 0;

	float radius;

protected:
	TransformComponent*				_transformComponent;
	RigidBodyComponent*				_rigidyBodyComponent;
};

