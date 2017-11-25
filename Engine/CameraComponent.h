#pragma once

#include "IComponent.h"

#include "TransformComponent.h"

class CameraComponent : public IComponent
{
public:
	CameraComponent();
	~CameraComponent();

private:
	TransformComponent*				_transform;
};