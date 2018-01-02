#include "TransformComponent.h"



TransformComponent::TransformComponent(Vec2 position, float rotation, float scale)
{
	_type = "Transform";
	_pos = Vec2();
	_rot = 0;
	_scale = 1;
	_hasChanged = false;

	_pos = position;
	mPreviousPosition = _pos;
	_scale = scale;
	_rot = rotation;
}


TransformComponent::~TransformComponent()
{
}

void TransformComponent::SetPosition(Vec2 position)
{
	if (position.x != _pos.x || position.y != _pos.y)
	{
		_hasChanged = true;
	}

	mPreviousPosition = _pos;
	_pos = position;
}