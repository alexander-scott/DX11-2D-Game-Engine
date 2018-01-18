#pragma once

#include "TransformComponent.h"
#include "ICamera.h"

class IDrawable
{
public:
	// Draw function must be overriden
	virtual void Draw(ICamera* cam) = 0;

	void SetTransform(TransformComponent* transform) { mTransform = transform; }
	TransformComponent* GetTransform() { return mTransform; }

	int						RenderLayer;

private:
	TransformComponent *	mTransform;
};