#pragma once

#include "Camera.h"

class EditorCamera : public Camera
{
public:
	EditorCamera(IGraphics* graphics);
	~EditorCamera();

	virtual void Update(float deltaTime) override;
};

