#include "Camera.h"


Camera::Camera(IGraphics* graphics)
	: GameObject("MainCamera", -1), // TODO: REMOVE HARDCODED -1
	ICamera(graphics)
{
	mTransform = ComponentFactory::MakeTransform(Vec2(0, 0), 0, 0);
	AddComponent(mTransform);
}

Camera::~Camera()
{
}

void Camera::DrawSpriteScreenSpace(std::string name, Vec2 pos, RECT * rect, float rot, float scale, Vec2 offset)
{
	gfx->DrawSprite(name, pos, rect, rot, scale, offset);
}

void Camera::DrawSpriteWorldSpace(std::string name, Vec2 pos, RECT * rect, float rot, float scale, Vec2 offset)
{
	gfx->DrawSprite(name, pos - mTransform->GetPosition(), rect, rot, scale, offset);
}

void Camera::DrawTextScreenSpace(std::string text, Vec2 pos, float rot, float* rgb, float scale, Vec2 offset)
{
	gfx->DrawText(text, pos, rot, rgb, scale, offset);
}

void Camera::DrawTextWorldSpace(std::string text, Vec2 pos, float rot, float* rgb, float scale, Vec2 offset)
{
	gfx->DrawText(text, pos - mTransform->GetPosition(), rot, rgb, scale, offset);
}

void Camera::DrawLine(Vec2 v1, Vec2 v2)
{
	Vec2 newV1 = v1 - mTransform->GetPosition();
	Vec2 newV2 = v2 - mTransform->GetPosition();
	gfx->DrawLine(v1, v2);
}
