#include "EditorCamera.h"

EditorCamera::EditorCamera(IGraphics* graphics) : ICameraGameObject(graphics)
{
	mPreviousMousePos = Mouse::Instance().GetPos();
	mRightPressed = false;
}

void EditorCamera::Update(float deltaTime)
{
	// Update camera based on right click drag
	if (Mouse::Instance().RightIsPressed())
	{
		// If the mouse wasn't being pressed the previous frame, reset the prevous mouse position
		if (!mRightPressed)
		{
			mRightPressed = true;
			mPreviousMousePos = Mouse::Instance().GetPos();
		}

		Vec2 newMousePos = Mouse::Instance().GetPos();

		Vec2 moveDir = newMousePos - mPreviousMousePos;
		float moveDist = moveDir.Len();
		float moveSpeed = moveDist / deltaTime;
		
		moveDir.Normalize();

		Vec2 currentPosition = GetPosition();
		currentPosition = currentPosition + (-moveDir * deltaTime * moveSpeed);

		mTransform->SetWorldPosition(currentPosition);

		mPreviousMousePos = newMousePos;
	}
	else if (!Mouse::Instance().RightIsPressed())
	{
		mRightPressed = false;
	}
}

void EditorCamera::DrawSpriteScreenSpace(std::string name, Vec2 pos, RECT * rect, float rot, float scale, Vec2 offset)
{
	gfx->DrawSprite(name, pos, rect, rot, scale, offset);
}

void EditorCamera::DrawSpriteWorldSpace(std::string name, Vec2 pos, RECT * rect, float rot, float scale, Vec2 offset)
{
	gfx->DrawSprite(name, pos - mTransform->GetWorldPosition(), rect, rot, scale, offset);
}

void EditorCamera::DrawTextScreenSpace(std::string text, Vec2 pos, float rot, float* rgb, float scale, Vec2 offset)
{
	gfx->DrawText(text, pos, rot, rgb, scale, offset);
}

void EditorCamera::DrawTextWorldSpace(std::string text, Vec2 pos, float rot, float* rgb, float scale, Vec2 offset)
{
	gfx->DrawText(text, pos - mTransform->GetWorldPosition(), rot, rgb, scale, offset);
}

void EditorCamera::DrawLine(Vec2 v1, Vec2 v2)
{
	Vec2 newV1 = v1 - mTransform->GetWorldPosition();
	Vec2 newV2 = v2 - mTransform->GetWorldPosition();
	gfx->DrawLine(v1, v2);
}