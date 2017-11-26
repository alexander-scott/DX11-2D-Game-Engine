#pragma once

#include "MainWindow.h"

#include "DX11Graphics.h"
//#include "ComponentFactory.h"

class Camera
{
public:
	Camera(class MainWindow& wnd);
	~Camera();

	IGraphics* GetGraphics() { return gfx; }

private:
	//TransformComponent* cameraTransform;
	IGraphics* gfx;
};

