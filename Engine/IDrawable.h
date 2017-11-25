#pragma once

#include "TransformComponent.h"
#include "IGraphics.h"

class IDrawable
{
public:
	virtual void Draw(IGraphics& gfx) = 0;
	void SetTransform(TransformComponent* transform) { _transform = transform; }

	TransformComponent* GetTransform() { return _transform; }

private:
	TransformComponent * _transform;
};