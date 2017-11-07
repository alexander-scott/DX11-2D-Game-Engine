#pragma once

#include "TransformComponent.h"
#include "Graphics.h"

class IDrawable
{
public:
	virtual void Draw(Graphics& gfx) = 0;
	void SetTransform(TransformComponent* transform) { _transform = transform; }

	TransformComponent* GetTransform() 
	{ 
		if (_transform == nullptr)
		{
			throw std::exception("This object requires a transform component.");
		}

		return _transform; 
	}

private:
	TransformComponent * _transform;
};