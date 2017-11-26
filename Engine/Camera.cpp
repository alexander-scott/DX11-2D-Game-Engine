#include "Camera.h"

Camera::Camera(class MainWindow& wnd)
{
	gfx = new DX11Graphics(); // PICK GRAPHICS INTERFACE
	gfx->Initalise(wnd);
	gfx->PreloadTextures();

	_pos = Vec2(0, 0);
}

Camera::~Camera()
{
	delete gfx;
}

void Camera::DrawSprite(std::string name, Vec2 pos, RECT * rect, float rot)
{
	Vec2 newPos = pos - _pos;
	gfx->DrawSprite(name, newPos, rect, rot);
}

void Camera::DrawSprite(std::string name, Vec2 pos, RECT * rect, float rot, float scale)
{
	Vec2 newPos = pos - _pos;
	gfx->DrawSprite(name, newPos, rect, rot, scale);
}

void Camera::DrawText(std::string text, Vec2 pos)
{
	Vec2 newPos = pos - _pos;
	gfx->DrawText(text, newPos);
}

void Camera::DrawLine(Vec2 v1, Vec2 v2)
{
	Vec2 newV1 = v1 - _pos;
	Vec2 newV2 = v2 - _pos;
	gfx->DrawLine(newV1, newV2);
}
