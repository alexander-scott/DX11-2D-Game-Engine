#include "MainWindow.h"
#include "Game.h"
#include "CustomException.h"

#define DllExport __declspec(dllexport)

// include the Direct3D Library file
#pragma comment (lib, "d3d11.lib")

extern "C" { DllExport void* InitD3D(HWND hWnd, int Width, int Height, const char* filePath); }

extern "C" { DllExport void StartUpdateLoop(void* gamePtr); }

extern "C" { DllExport void CleanD3D(void* gamePtr); }

extern "C" { DllExport void MouseMove(void* gamePtr, int xPos, int yPos); }
extern "C" { DllExport void MouseClick(void* gamePtr, int xPos, int yPos); }
extern "C" { DllExport void MouseRelease(void* gamePtr, int xPos, int yPos); }

extern "C" { DllExport void KeyDown(void* gamePtr, int keyCode); }
extern "C" { DllExport void KeyUp(void* gamePtr, int keyCode); }

void* InitD3D(HWND hWnd, int Width, int Height, const char* filePath)
{
	try
	{
		MainWindow wnd(hWnd, Width, Height);
		try
		{
			Game* theGame = new Game(wnd, Width, Height, filePath);
			return theGame;
		}
		catch (const CustomException& e)
		{
			const std::wstring eMsg = e.GetFullMessage() +
				L"\n\nException caught at Windows message loop.";
			wnd.ShowMessageBox(e.GetExceptionType(), eMsg, MB_ICONERROR);
		}
		catch (const std::exception& e)
		{
			// need to convert std::exception what() string from narrow to wide string
			const std::string whatStr(e.what());
			const std::wstring eMsg = std::wstring(whatStr.begin(), whatStr.end()) +
				L"\n\nException caught at Windows message loop.";
			wnd.ShowMessageBox(L"Unhandled STL Exception", eMsg, MB_ICONERROR);
		}
		catch (...)
		{
			wnd.ShowMessageBox(L"Unhandled Non-STL Exception",
				L"\n\nException caught at Windows message loop.", MB_ICONERROR);
		}
	}
	catch (const CustomException& e)
	{
		const std::wstring eMsg = e.GetFullMessage() +
			L"\n\nException caught at main window creation.";
		MessageBox(nullptr, eMsg.c_str(), e.GetExceptionType().c_str(), MB_ICONERROR);
	}
	catch (const std::exception& e)
	{
		// need to convert std::exception what() string from narrow to wide string
		const std::string whatStr(e.what());
		const std::wstring eMsg = std::wstring(whatStr.begin(), whatStr.end()) +
			L"\n\nException caught at main window creation.";
		MessageBox(nullptr, eMsg.c_str(), L"Unhandled STL Exception", MB_ICONERROR);
	}
	catch (...)
	{
		MessageBox(nullptr, L"\n\nException caught at main window creation.",
			L"Unhandled Non-STL Exception", MB_ICONERROR);
	}

	return nullptr;
}

void StartUpdateLoop(void * gamePtr)
{
	Game* thisGame = static_cast<Game*>(gamePtr);
	while (thisGame->wnd.ProcessMessage())
	{
		thisGame->Update();
	}
}

void CleanD3D(void * gamePtr)
{
	Game* thisGame = static_cast<Game*>(gamePtr);
	delete thisGame;
}

void MouseMove(void * gamePtr, int xPos, int yPos)
{
	Game* thisGame = static_cast<Game*>(gamePtr);
	thisGame->wnd.ProcessMouseMove(xPos, yPos);
}

void MouseClick(void * gamePtr, int xPos, int yPos)
{
	Game* thisGame = static_cast<Game*>(gamePtr);
	thisGame->wnd.ProcessMouseClick(xPos, yPos);
}

void MouseRelease(void * gamePtr, int xPos, int yPos)
{
	Game* thisGame = static_cast<Game*>(gamePtr);
	thisGame->wnd.ProcessMouseRelease(xPos, yPos);
}

void KeyDown(void * gamePtr, int keyCode)
{
	Game* thisGame = static_cast<Game*>(gamePtr);
	thisGame->wnd.ProcessKeyPressed(keyCode);
}

void KeyUp(void * gamePtr, int keyCode)
{
	Game* thisGame = static_cast<Game*>(gamePtr);
	thisGame->wnd.ProcessKeyReleased(keyCode);
}
