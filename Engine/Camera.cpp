#include "Camera.h"

Camera::Camera(class MainWindow& wnd)
{
	gfx = new DX11Graphics(); // PICK GRAPHICS INTERFACE
	gfx->Initalise(wnd);
	gfx->PreloadTextures();

	// TRANSFORM COMPONENT
	//TransformComponent* playerTransform = ComponentFactory::MakeTransform(Vec2(350, 150), 0, 1);
	//AddComponent(playerTransform);
}

Camera::~Camera()
{
	delete gfx;
}
