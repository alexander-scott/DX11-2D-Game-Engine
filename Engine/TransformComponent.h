#pragma once

#include "IComponent.h"
#include "IEMath.h"

class TransformComponent : public IComponent
{
public:
	TransformComponent(Vec2 position, float rotation, float scale);
	~TransformComponent();

	void SetPosition(Vec2 position);
	void SetPreviousPosition(Vec2 position) { mPreviousPosition = position; }

	void SetScale(float scale) { mScale = scale; }
	void SetRotation(float rot) { mRotation = rot; }

	float GetRotation() const { return mRotation; }
	float GetScale() const { return mScale; }
	Vec2 GetPosition() const { return mPosition; }

	Vec2 GetPreviousPosition() const { return mPreviousPosition; }

	bool CheckChanged() { return mHasChanged; }
	void SetChanged(bool changed) { mHasChanged = changed; }

private:
	Vec2					mPosition;
	float					mRotation; // RADIANS
	float					mScale;

	bool					mHasChanged;
	Vec2					mPreviousPosition;
};