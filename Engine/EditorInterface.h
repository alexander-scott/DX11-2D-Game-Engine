#pragma once

#include "MainWindow.h"
#include "Engine.h"

#define DllExport __declspec(dllexport)

// include the Direct3D Library file
#pragma comment (lib, "d3d11.lib")

namespace EditorInterface
{
	extern "C" { DllExport void* InitaliseEngine(HWND hWnd, int Width, int Height, const char* filePath); }

	extern "C" { DllExport void StartUpdateLoop(void* gamePtr); }

	extern "C" { DllExport void CleanD3D(void* gamePtr); }

	extern "C" { DllExport void MouseMove(void* gamePtr, int xPos, int yPos); }
	extern "C" { DllExport void MouseClick(void* gamePtr, int xPos, int yPos); }
	extern "C" { DllExport void MouseRelease(void* gamePtr, int xPos, int yPos); }

	extern "C" { DllExport void KeyDown(void* gamePtr, int keyCode); }
	extern "C" { DllExport void KeyUp(void* gamePtr, int keyCode); }
}