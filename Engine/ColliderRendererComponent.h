#pragma once

#include "IComponent.h"
#include "IDrawable.h"

#include "ColliderComponent.h"
#include "PolygonColliderComponent.h"

// BROKEN
class ColliderRendererComponent : public IComponent, public IDrawable
{
public:
	ColliderRendererComponent();
	~ColliderRendererComponent();

	void SetCollider(ColliderComponent* collider);

	virtual void Draw(Camera* cam) override;

private:
	ColliderComponent*				_collider;
	ColliderType					_colliderType;
};

