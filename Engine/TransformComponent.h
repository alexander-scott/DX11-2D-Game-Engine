#pragma once

#include "IComponent.h"
#include "IEMath.h"

class TransformComponent : public IComponent
{
private:
	Vec2					_pos;
	float					_rot;

public:
	TransformComponent();
	~TransformComponent();

	void SetPosition(float x, float y, float z) { _pos = Vec2(x, y); }
	void SetPosition(Vec2 position) { _pos = position; }

	void SetRotation(float rot) { _rot = rot; }

	float GetRotation() const { return _rot; }
	Vec2 GetPosition() const { return _pos; }
};