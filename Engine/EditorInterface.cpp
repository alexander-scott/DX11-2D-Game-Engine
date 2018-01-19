#include "EditorInterface.h"

namespace EditorInterface
{
	void* InitaliseEngine(HWND hWnd, int Width, int Height, const char* filePath)
	{
		try
		{
			MainWindow wnd(hWnd, Width, Height);
			try
			{
				Engine* theGame = new Engine(wnd, Width, Height, filePath);
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

	void StartUpdateLoop(void * enginePtr)
	{
		Engine* engine = static_cast<Engine*>(enginePtr);
		while (engine->wnd.ProcessMessage())
		{
			engine->Update();
		}
	}

	void CleanD3D(void * enginePtr)
	{
		Engine* engine = static_cast<Engine*>(enginePtr);
		delete engine;
	}

	void MouseMove(void * enginePtr, int xPos, int yPos)
	{
		Engine* engine = static_cast<Engine*>(enginePtr);
		engine->wnd.ProcessMouseMove(xPos, yPos);
	}

	void MouseClick(void * enginePtr, int xPos, int yPos)
	{
		Engine* engine = static_cast<Engine*>(enginePtr);
		engine->wnd.ProcessMouseClick(xPos, yPos);
	}

	void MouseRelease(void * enginePtr, int xPos, int yPos)
	{
		Engine* engine = static_cast<Engine*>(enginePtr);
		engine->wnd.ProcessMouseRelease(xPos, yPos);
	}

	void KeyDown(void * enginePtr, int keyCode)
	{
		Engine* engine = static_cast<Engine*>(enginePtr);
		engine->wnd.ProcessKeyPressed(keyCode);
	}

	void KeyUp(void * enginePtr, int keyCode)
	{
		Engine* engine = static_cast<Engine*>(enginePtr);
		engine->wnd.ProcessKeyReleased(keyCode);
	}
}