#pragma once

#include "MainWindow.h"

#include "DX11Graphics.h"

class ICamera
{
public:
	ICamera(IGraphics* graphics) : gfx(graphics) {}

	void BeginFrame() { gfx->BeginFrame(); }
	void EndFrame() { gfx->EndFrame(); }

	virtual void DrawSpriteScreenSpace(std::string name, Vec2 pos, RECT* rect, float rot, float scale, Vec2 offset) = 0;
	virtual void DrawSpriteWorldSpace(std::string name, Vec2 pos, RECT* rect, float rot, float scale, Vec2 offset) = 0;

	virtual void DrawTextScreenSpace(std::string text, Vec2 pos, float rot, float* rgb, float scale, Vec2 offset) = 0;
	virtual void DrawTextWorldSpace(std::string text, Vec2 pos, float rot, float* rgb, float scale, Vec2 offset) = 0;

	virtual void DrawLine(Vec2 v1, Vec2 v2) = 0;

protected:
	IGraphics* gfx;
};

