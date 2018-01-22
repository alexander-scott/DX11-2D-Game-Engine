#include "EditorCamera.h"

EditorCamera::EditorCamera(IGraphics* graphics) : ICameraGameObject(graphics)
{
}

void EditorCamera::Update(float deltaTime)
{
	// Update camera based on right click drag
}

void EditorCamera::DrawSpriteScreenSpace(std::string name, Vec2 pos, RECT * rect, float rot, float scale, Vec2 offset)
{
	gfx->DrawSprite(name, pos, rect, rot, scale, offset);
}

void EditorCamera::DrawSpriteWorldSpace(std::string name, Vec2 pos, RECT * rect, float rot, float scale, Vec2 offset)
{
	gfx->DrawSprite(name, pos - mTransform->GetPosition(), rect, rot, scale, offset);
}

void EditorCamera::DrawTextScreenSpace(std::string text, Vec2 pos, float rot, float* rgb, float scale, Vec2 offset)
{
	gfx->DrawText(text, pos, rot, rgb, scale, offset);
}

void EditorCamera::DrawTextWorldSpace(std::string text, Vec2 pos, float rot, float* rgb, float scale, Vec2 offset)
{
	gfx->DrawText(text, pos - mTransform->GetPosition(), rot, rgb, scale, offset);
}

void EditorCamera::DrawLine(Vec2 v1, Vec2 v2)
{
	Vec2 newV1 = v1 - mTransform->GetPosition();
	Vec2 newV2 = v2 - mTransform->GetPosition();
	gfx->DrawLine(v1, v2);
}