#pragma once

#include "IComponent.h"
#include "IEMath.h"

class TransformComponent : public IComponent
{
private:
	Vec2					_pos;
	float					_rot; // RADIANS
	float					_scale;

	bool					_hasChanged;
	Vec2					mPreviousPosition;

public:
	TransformComponent(Vec2 position, float rotation, float scale);
	~TransformComponent();

	void SetPosition(Vec2 position);
	void SetPreviousPosition(Vec2 position) { mPreviousPosition = position; }

	void SetScale(float scale) { _scale = scale; }
	void SetRotation(float rot) { _rot = rot; }

	float GetRotation() const { return _rot; }
	float GetScale() const { return _scale; }
	Vec2 GetPosition() const { return _pos; }

	Vec2 GetPreviousPosition() const { return mPreviousPosition; }

	bool CheckChanged() { return _hasChanged; }
	void SetChanged(bool changed) { _hasChanged = changed; }
};