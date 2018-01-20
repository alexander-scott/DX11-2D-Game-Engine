#pragma once

#include "MainWindow.h"
#include "Engine.h"

#define DllExport __declspec(dllexport)

// include the Direct3D Library file
#pragma comment (lib, "d3d11.lib")

namespace EditorInterface
{
	extern "C" { DllExport void* InitaliseEngine(HWND hWnd, int Width, int Height, const char* filePath); }

	extern "C" { DllExport void StartEditorLoop(void* enginePtr); }
	extern "C" { DllExport void StartUpdateLoop(void* enginePtr); }

	extern "C" { DllExport void CleanD3D(void* enginePtr); }

	extern "C" { DllExport void MouseMove(void* enginePtr, int xPos, int yPos); }
	extern "C" { DllExport void MouseClick(void* enginePtr, int xPos, int yPos); }
	extern "C" { DllExport void MouseRelease(void* enginePtr, int xPos, int yPos); }

	extern "C" { DllExport void KeyDown(void* enginePtr, int keyCode); }
	extern "C" { DllExport void KeyUp(void* enginePtr, int keyCode); }
}