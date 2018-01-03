#include "GameCamera.h"



GameCamera::GameCamera() : GameObject("GameCamera")
{

}


GameCamera::~GameCamera()
{
}

void GameCamera::Initalise(MainWindow & wnd)
{
	gfx = new DX11Graphics(); // DECIDE ON GRAPHICS API HERE

	mTransform = ComponentFactory::MakeTransform(Vec2(0, 0), 0, 0);
	AddComponent(mTransform);

	ICamera::Initalise(wnd);
}

void GameCamera::Update(float deltaTime)
{
	GameObject::Update(deltaTime);

	// Set the cameras central position to be on the focus position
	Vec2 pos = mFocusTrans->GetPosition();

	if (pos.x - ((SCREEN_WIDTH / 2) - 32) < mLevelLeftBound)
	{
		pos.x = mLevelLeftBound + ((SCREEN_WIDTH / 2) - 32);
	}

	if (pos.x + ((SCREEN_WIDTH / 2) + 32) > mLevelRightBound)
	{
		pos.x = mLevelRightBound - ((SCREEN_WIDTH / 2) + 32);
	}

	if (pos.y + ((SCREEN_HEIGHT / 2) + 32) > mLevelBottomBound)
	{
		pos.y = mLevelBottomBound - ((SCREEN_HEIGHT / 2) + 32);
	}

	if (pos.y - ((SCREEN_HEIGHT / 2) - 32) < mLevelTopBound)
	{
		pos.y = mLevelTopBound + ((SCREEN_HEIGHT / 2) - 32);
	}

	pos.x -= (SCREEN_WIDTH / 2) - 32; // -32 because that is the exact centre of the player sprite
	pos.y -= (SCREEN_HEIGHT / 2) - 32;

	mTransform->SetPosition(pos);
}

void GameCamera::DrawSprite(std::string name, Vec2 pos, RECT * rect, float rot, float scale, Vec2 offset)
{
	gfx->DrawSprite(name, pos - mTransform->GetPosition(), rect, rot, scale, offset);
}

void GameCamera::DrawTextScreenSpace(std::string text, Vec2 pos, float rot, float* rgb, float scale)
{
	gfx->DrawText(text, pos, rot, rgb, scale);
}

void GameCamera::DrawTextWorldSpace(std::string text, Vec2 pos, float rot, float* rgb, float scale)
{
	gfx->DrawText(text, pos - mTransform->GetPosition(), rot, rgb, scale);
}

void GameCamera::DrawLine(Vec2 v1, Vec2 v2)
{
	Vec2 newV1 = v1 - mTransform->GetPosition();
	Vec2 newV2 = v2 - mTransform->GetPosition();
	gfx->DrawLine(v1, v2);
}
