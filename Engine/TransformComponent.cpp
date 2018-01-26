#include "TransformComponent.h"

// TODO:
// - Remove world members all together. Although still provide the function to return world values but this is calculated by multiplying local values by parent world values 
// - Initalise transform components with local values
// - Setting local values simply sets member values
// - Setting world values sets local member values to the difference between the new value and the parent value

TransformComponent::TransformComponent(Vec2 localPosition, float localRotation, float localScale)
{
	mType = "Transform";
	mHasChanged = false;

	mLocalPosition = localPosition;
	mLocalScale = localScale;
	mLocalRotation = localRotation;

	mParent = nullptr;
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
	// Calculate the new position
	Vec2 newPos;
	if (mParent != nullptr)
		newPos = position - mParent->GetWorldPosition();
	else
		newPos = position;

	// If the new position is different to the old postion set hasChanged to true
	if (newPos.x != mLocalPosition.x || newPos.y != mLocalPosition.y)
		mHasChanged = true;

	mLocalPosition = newPos;
}

void TransformComponent::SetWorldScale(float scale)
{
	float newScale;
	if (mParent != nullptr)
		newScale = (mParent->GetWorldScale() + scale) / 2;
	else
		newScale = scale;

	if (newScale != mLocalScale)
		mHasChanged = true;

	mLocalScale = newScale;
}

void TransformComponent::SetWorldRotation(float rot)
{
	float newRot;
	if (mParent != nullptr)
		newRot = rot - mParent->GetWorldRotation();
	else
		newRot = rot;

	if (newRot != mLocalRotation)
		mHasChanged = true;

	mLocalRotation = newRot;
}

float TransformComponent::GetWorldRotation() const
{
	if (mParent != nullptr)
		return mLocalRotation + mParent->GetWorldRotation();
	else
		return mLocalRotation;
}

float TransformComponent::GetWorldScale() const
{
	if (mParent != nullptr)
		return mLocalScale * mParent->GetWorldScale();
	else
		return mLocalScale;
}

Vec2 TransformComponent::GetWorldPosition() const
{
	if (mParent != nullptr)
		return mLocalPosition + mParent->GetWorldPosition();
	else
		return mLocalPosition;
}