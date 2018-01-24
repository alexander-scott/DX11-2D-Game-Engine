#pragma once

#include "IComponent.h"
#include "Consts.h"

class TransformComponent : public IComponent
{
public:
	TransformComponent(Vec2 position, float rotation, float scale);

	void SetWorldPosition(Vec2 position);
	void SetWorldScale(float scale);
	void SetWorldRotation(float rot);

	float GetWorldRotation() const;
	float GetWorldScale() const;
	Vec2 GetWorldPosition() const;

	bool CheckChanged() { return mHasChanged; }
	void SetChanged(bool changed) { mHasChanged = changed; }

	void SetParent(TransformComponent* parent) { mParent = parent; }

private:
	Vec2					mLocalPosition;
	float					mLocalRotation; // RADIANS
	float					mLocalScale;

	Vec2					mWorldPosition;
	float					mWorldRotation; // RADIANS
	float					mWorldScale;

	bool					mHasChanged;

	TransformComponent*		mParent;
};