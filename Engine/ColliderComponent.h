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

	void SetOrient(float radians) { orientationMatrix.Set(radians); }

	virtual ColliderType GetType(void) const = 0;

	float radius;
	Mat2 orientationMatrix;

protected:
	TransformComponent*				_transformComponent;
	RigidBodyComponent*				_rigidyBodyComponent;
};

