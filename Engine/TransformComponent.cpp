#include "TransformComponent.h"



TransformComponent::TransformComponent(Vec2 position, float rotation, float scale)
{
	mType = "Transform";
	mPosition = Vec2();
	mRotation = 0;
	mScale = 1;
	mHasChanged = false;

	mPosition = position;
	mPreviousPosition = mPosition;
	mScale = scale;
	mRotation = rotation;
}


TransformComponent::~TransformComponent()
{
}

void TransformComponent::SetPosition(Vec2 position)
{
	if (position.x != mPosition.x || position.y != mPosition.y)
	{
		mHasChanged = true;
	}

	mPreviousPosition = mPosition;
	mPosition = position;
}