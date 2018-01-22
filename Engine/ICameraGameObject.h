#pragma once

#include "ICamera.h"
#include "GameObject.h"
#include "GameComponentFactory.h"

class ICameraGameObject : public ICamera, public GameObject
{
public:
	ICameraGameObject(IGraphics* graphics) : ICamera(graphics), GameObject("MainCamera", -1) // TODO: REMOVE HARDCODED -1
	{
		mTransform = ComponentFactory::MakeTransform(Vec2(0, 0), 0, 0);
		AddComponent(mTransform);
	} 

	Vec2 GetPosition() { return mTransform->GetPosition(); }

protected:
	TransformComponent * mTransform;
};