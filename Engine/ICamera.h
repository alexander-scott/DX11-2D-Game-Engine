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

	virtual void Update(float deltaTime) { }

	void BeginFrame() { gfx->BeginFrame(); }
	void EndFrame() { gfx->EndFrame(); }

	Vec2 GetPos() { return _pos; }

	void DrawSprite(std::string name, Vec2 pos, RECT* rect, float rot) {
		gfx->DrawSprite(name, pos - _pos, rect, rot);
	}

	void DrawSprite(std::string name, Vec2 pos, RECT* rect, float rot, float scale) {
		gfx->DrawSprite(name, pos - _pos, rect, rot, scale);
	}

	void DrawText(std::string text, Vec2 pos) {
		gfx->DrawText(text, pos - _pos);
	}

	void DrawLine(Vec2 v1, Vec2 v2) {
		Vec2 newV1 = v1 - _pos;	Vec2 newV2 = v2 - _pos;	gfx->DrawLine(newV1, newV2);
	}

protected:
	Vec2 _pos = Vec2(0, 0);
	IGraphics* gfx;
};

