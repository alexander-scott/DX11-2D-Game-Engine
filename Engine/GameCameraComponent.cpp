#include "GameCameraComponent.h"

GameCameraComponent::GameCameraComponent(TransformComponent* trans, TransformComponent* fTrans)
{
	mTransform = trans;
	mFocusTrans = fTrans;
}

GameCameraComponent::~GameCameraComponent()
{
}

void GameCameraComponent::Update(float deltaTime)
{
	// Set the cameras central position to be on the focus position
	Vec2 pos = mFocusTrans->GetPosition();
/*
	if (pos.x - ((ApplicationValues::Instance().ScreenWidth / 2) - 32) < mLevelLeftBound)
	{
		pos.x = mLevelLeftBound + ((ApplicationValues::Instance().ScreenWidth / 2) - 32);
	}

	if (pos.x + ((ApplicationValues::Instance().ScreenWidth / 2) + 32) > mLevelRightBound)
	{
		pos.x = mLevelRightBound - ((ApplicationValues::Instance().ScreenWidth / 2) + 32);
	}

	if (pos.y + ((ApplicationValues::Instance().ScreenHeight / 2) + 32) > mLevelBottomBound)
	{
		pos.y = mLevelBottomBound - ((ApplicationValues::Instance().ScreenHeight / 2) + 32);
	}

	if (pos.y - ((ApplicationValues::Instance().ScreenHeight / 2) - 32) < mLevelTopBound)
	{
		pos.y = mLevelTopBound + ((ApplicationValues::Instance().ScreenHeight / 2) - 32);
	}*/

	pos.x -= (ApplicationValues::Instance().ScreenWidth / 2) - 32; // -32 because that is the exact centre of the player sprite
	pos.y -= (ApplicationValues::Instance().ScreenHeight / 2) - 32;

	mTransform->SetPosition(pos);
}
