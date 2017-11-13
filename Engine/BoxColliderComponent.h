#pragma once

#include "ColliderComponent.h"

class BoxColliderComponent : public ColliderComponent
{
public:
	BoxColliderComponent();
	~BoxColliderComponent();

	void SetAABB(float width, float height) { _width = width; _height = height; }
	virtual Collider ReturnCollider() override;

private:
	float			_width;
	float			_height;
};

