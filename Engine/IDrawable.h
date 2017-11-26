#pragma once

#include "TransformComponent.h"
#include "ICamera.h"

class IDrawable
{
public:
	virtual void Draw(ICamera* cam) = 0;
	void SetTransform(TransformComponent* transform) { _transform = transform; }

	TransformComponent* GetTransform() { return _transform; }

private:
	TransformComponent * _transform;
};