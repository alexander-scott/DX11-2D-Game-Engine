#include "TransformComponent.h"

TransformComponent::TransformComponent(Vec2 position, float rotation, float scale)
{
	mType = "Transform";
	mWorldPosition = Vec2();
	mWorldRotation = 0;
	mWorldScale = 1;
	mHasChanged = false;

	mWorldPosition = position;
	mWorldScale = scale;
	mWorldRotation = rotation;
}

void TransformComponent::SetWorldPosition(Vec2 position)
{
	if (position.x != mWorldPosition.x || position.y != mWorldPosition.y)
	{
		mHasChanged = true;
	}

	mWorldPosition = position;
}

void TransformComponent::SetWorldScale(float scale)
{
	if (scale != mWorldScale)
	{
		mHasChanged = true;
	}

	mWorldScale = scale;
}

void TransformComponent::SetWorldRotation(float rot)
{
	if (rot != mWorldRotation)
	{
		mHasChanged = true;
	}

	mWorldRotation = rot;
}

float TransformComponent::GetWorldRotation() const
{
	return mWorldRotation;
}

float TransformComponent::GetWorldScale() const
{
	return mWorldScale;
}

Vec2 TransformComponent::GetWorldPosition() const
{
	return mWorldPosition;
}