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

void TransformComponent::SetPosition(Vec2 position)
{
	if (position.x != _pos.x || position.y != _pos.y)
	{
		_hasChanged = true;
	}

	_pos = position;
}
