#pragma once

#include "MainWindow.h"

#include "DX11Graphics.h"

class ICamera
{
public:
	void Initalise(class MainWindow& wnd)
	{
		gfx->Initalise(wnd); // Decide on Graphics API in child constructor
		gfx->PreloadTextures();
	}

	void Destroy()
	{
		gfx->Destroy();
		delete gfx;
	}

	void BeginFrame() { gfx->BeginFrame(); }
	void EndFrame() { gfx->EndFrame(); }

	virtual void DrawSprite(std::string name, Vec2 pos, RECT* rect, float rot) = 0;
	virtual void DrawSprite(std::string name, Vec2 pos, RECT* rect, float rot, float scale) = 0;
	virtual void DrawText(std::string text, Vec2 pos) = 0;
	virtual void DrawLine(Vec2 v1, Vec2 v2) = 0;

protected:
	IGraphics* gfx;
};

