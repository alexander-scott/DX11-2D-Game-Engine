#pragma once

#include "IComponent.h"
#include "IEMath.h"

class TransformComponent : public IComponent
{
private:
	Vec2					_pos;
	float					_rot; // RADIANS
	float					_scale;

public:
	TransformComponent();
	~TransformComponent();

	void SetPosition(float x, float y) { _pos = Vec2(x, y); }
	void SetPosition(Vec2 position) { _pos = position; }

	void SetScale(float scale) { _scale = scale; }
	void SetRotation(float rot) { _rot = rot; }

	float GetRotation() const { return _rot; }
	float GetScale() const { return _scale; }
	Vec2 GetPosition() const { return _pos; }
};