#pragma once

#include "TransformComponent.h"
#include "Camera.h"

class IDrawable
{
public:
	virtual void Draw(Camera* cam) = 0;
	void SetTransform(TransformComponent* transform) { _transform = transform; }

	TransformComponent* GetTransform() { return _transform; }

private:
	TransformComponent * _transform;
};