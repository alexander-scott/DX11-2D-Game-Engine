#include "TransformComponent.h"



TransformComponent::TransformComponent()
{
	_type = "Transform";
	_pos = Vec2();
	_rot = 0;
	_scale = 1;
}


TransformComponent::~TransformComponent()
{
}
