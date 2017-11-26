#pragma once

#include "MainWindow.h"

#include "DX11Graphics.h"

class Camera
{
public:
	Camera(class MainWindow& wnd);
	~Camera();

	void BeginFrame() { gfx->BeginFrame(); }
	void EndFrame() { gfx->EndFrame(); }

	void DrawSprite(std::string name, Vec2 pos, RECT* rect, float rot);
	void DrawSprite(std::string name, Vec2 pos, RECT* rect, float rot, float scale);
	void DrawText(std::string text, Vec2 pos);
	void DrawLine(Vec2 v1, Vec2 v2);

	Vec2 GetPos() { return _pos; }

private:
	IGraphics* gfx;

	Vec2				_pos;
};

