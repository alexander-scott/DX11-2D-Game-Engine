#include "TransformComponent.h"

TransformComponent::TransformComponent(Vec2 worldPosition, float worldRotation, float worldScale)
{
	mType = "Transform";
	mLocalPosition = Vec2();
	mLocalRotation = 0;
	mLocalScale = 1;
	mHasChanged = false;

	mWorldPosition = worldPosition;
	mWorldScale = worldScale;
	mWorldRotation = worldRotation;
}

void TransformComponent::SetLocalPosition(Vec2 position)
{
	if (position.x != mLocalPosition.x || position.y != mLocalPosition.y)
	{
		mHasChanged = true;
	}

	mLocalPosition = position;
}

void TransformComponent::SetLocalScale(float scale)
{
	if (scale != mLocalScale)
	{
		mHasChanged = true;
	}

	mLocalScale = scale;
}

void TransformComponent::SetLocalRotation(float rot)
{
	if (rot != mLocalRotation)
	{
		mHasChanged = true;
	}

	mLocalRotation = rot;
}

float TransformComponent::GetLocalRotation() const
{
	return mLocalRotation;
}

float TransformComponent::GetLocalScale() const
{
	return mLocalScale;
}

Vec2 TransformComponent::GetLocalPosition() const
{
	return mLocalPosition;
}

void TransformComponent::SetWorldPosition(Vec2 position)
{
	if (position.x != mWorldPosition.x || position.y != mWorldPosition.y)
	{
		mHasChanged = true;
	}
	else
	{
		return;
	}

	mWorldPosition = position;

	if (mParent != nullptr)
	{
		Vec2 parentPos = mParent->GetWorldPosition();

	}
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