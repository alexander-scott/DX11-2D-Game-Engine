#pragma once

#include "Camera.h"

class EditorCamera : public Camera
{
public:
	EditorCamera();
	~EditorCamera();

	virtual void Update(float deltaTime) override;
};

