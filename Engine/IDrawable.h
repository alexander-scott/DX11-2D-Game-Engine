#pragma once

#include "TransformComponent.h"
#include "Graphics.h"

class IDrawable
{
public:
	TransformComponent * _transform;

	virtual void Draw(Graphics& gfx) = 0;
	virtual void SetTransform(TransformComponent* transform) { _transform = transform; }
};