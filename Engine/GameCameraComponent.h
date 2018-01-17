#pragma once

#include "IComponent.h"
#include "IUpdateable.h"

#include "TransformComponent.h"

class GameCameraComponent : public IComponent, public IUpdateable
{
public:
	GameCameraComponent(TransformComponent* trans, TransformComponent* fTrans);
	~GameCameraComponent();

	void SetLevelBounds(float leftBound, float rightBound, float botBound, float topBound) { mLevelLeftBound = leftBound; mLevelRightBound = rightBound; mLevelBottomBound = botBound; mLevelTopBound = topBound; }

	virtual void Update(float deltaTime) override;

private:
	TransformComponent *	mTransform;
	TransformComponent *	mFocusTrans;

	float					mLevelLeftBound;
	float					mLevelRightBound;

	float					mLevelBottomBound;
	float					mLevelTopBound;
};

