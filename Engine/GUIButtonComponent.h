#pragma once

#include "IComponent.h"
#include "IUpdateable.h"

#include "PolygonColliderComponent.h"

#include "Mouse.h"

class GUIButtonComponent : public IComponent, public IUpdateable
{
public:
	GUIButtonComponent(TransformComponent* trans, float width, float height);
	~GUIButtonComponent();

	virtual void Update(float deltaTime) override;

	bool Clicked() { return mClicked; }

private:
	bool						mClicked;
	bool						mIsPressed;

	float						mWidth;
	float						mHeight;

	TransformComponent*			mTransform;

};