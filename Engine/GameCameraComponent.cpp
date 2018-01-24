#include "GameCameraComponent.h"

GameCameraComponent::GameCameraComponent(TransformComponent* trans, TransformComponent* fTrans, float fWidth, float fHeight)
	: mTransform(trans), mFocusTrans(fTrans)
{
	mType = "Game Camera";

	mFocusWidth = fWidth / 2;
	mFocusHeight = fHeight / 2;
}

GameCameraComponent::~GameCameraComponent()
{
}

void GameCameraComponent::Update(float deltaTime)
{
	// Set the cameras central position to be on the focus position
	Vec2 pos = mFocusTrans->GetWorldPosition();

	if (pos.x - ((ApplicationValues::Instance().ScreenWidth / 2) - mFocusWidth) < mLevelLeftBound)
	{
		pos.x = mLevelLeftBound + ((ApplicationValues::Instance().ScreenWidth / 2) - mFocusWidth);
	}
	else if (pos.x + ((ApplicationValues::Instance().ScreenWidth / 2) + mFocusWidth) > mLevelRightBound)
	{
		pos.x = mLevelRightBound - ((ApplicationValues::Instance().ScreenWidth / 2) + mFocusWidth);
	}

	if (pos.y + ((ApplicationValues::Instance().ScreenHeight / 2) + mFocusHeight) > -mLevelBottomBound)
	{
		pos.y = -mLevelBottomBound - ((ApplicationValues::Instance().ScreenHeight / 2) + mFocusHeight);
	}
	else if (pos.y - ((ApplicationValues::Instance().ScreenHeight / 2) - mFocusHeight) < -mLevelTopBound)
	{
		pos.y = -mLevelTopBound + ((ApplicationValues::Instance().ScreenHeight / 2) - mFocusHeight);
	}

	pos.x -= (ApplicationValues::Instance().ScreenWidth / 2) - mFocusWidth;
	pos.y -= (ApplicationValues::Instance().ScreenHeight / 2) - mFocusHeight;

	mTransform->SetWorldPosition(pos);
}
