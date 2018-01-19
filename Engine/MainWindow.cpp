#include "MainWindow.h"
#include "Resource.h"
#include "IGraphics.h"
#include "CustomException.h"
#include "Engine.h"
#include <assert.h>

MainWindow::MainWindow(HINSTANCE hInst, wchar_t * pArgs, int width, int height)
	:
	args(pArgs),
	hInst(hInst)
{
	// register window class
	WNDCLASSEX wc = { sizeof(WNDCLASSEX),CS_CLASSDC,_HandleMsgSetup,0,0,
		hInst,nullptr,nullptr,nullptr,nullptr,
		wndClassName,nullptr };
	wc.hIconSm = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDI_APPICON), IMAGE_ICON, 16, 16, 0);
	wc.hIcon = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDI_APPICON), IMAGE_ICON, 32, 32, 0);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	RegisterClassEx(&wc);

	// create window & get hWnd
	RECT wr;
	wr.left = 350;
	wr.right = width + wr.left;
	wr.top = 100;
	wr.bottom = height + wr.top;
	AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);
	hWnd = CreateWindow(wndClassName, L"DirectXTK Simple Sample",
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		wr.left, wr.top, wr.right - wr.left, wr.bottom - wr.top,
		nullptr, nullptr, hInst, this);

	// throw exception if something went terribly wrong
	if (hWnd == nullptr)
	{
		throw Exception(_CRT_WIDE(__FILE__), __LINE__,
			L"Failed to get valid window handle.");
	}

	HDEVNOTIFY hNewAudio = nullptr;
	DEV_BROADCAST_DEVICEINTERFACE filter = { 0 };
	filter.dbcc_size = sizeof(filter);
	filter.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
	filter.dbcc_classguid = KSCATEGORY_AUDIO;

	hNewAudio = RegisterDeviceNotification(hWnd, &filter,
		DEVICE_NOTIFY_WINDOW_HANDLE);

	if (hNewAudio)
		UnregisterDeviceNotification(hNewAudio);

	// show and update
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
}

MainWindow::MainWindow(HWND hwnd, int width, int height)
{
	// create window & get hWnd
	hWnd = hwnd;

	// throw exception if something went terribly wrong
	if (hWnd == nullptr)
	{
		throw Exception(_CRT_WIDE(__FILE__), __LINE__,
			L"Failed to get valid window handle.");
	}

	HDEVNOTIFY hNewAudio = nullptr;
	DEV_BROADCAST_DEVICEINTERFACE filter = { 0 };
	filter.dbcc_size = sizeof(filter);
	filter.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
	filter.dbcc_classguid = KSCATEGORY_AUDIO;

	hNewAudio = RegisterDeviceNotification(hWnd, &filter,
		DEVICE_NOTIFY_WINDOW_HANDLE);

	if (hNewAudio)
		UnregisterDeviceNotification(hNewAudio);

	// show and update
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
}

MainWindow::~MainWindow()
{
	// unregister window class
	UnregisterClass(wndClassName, hInst);
}

bool MainWindow::IsActive() const
{
	return GetActiveWindow() == hWnd;
}

bool MainWindow::IsMinimized() const
{
	return IsIconic(hWnd) != 0;
}

void MainWindow::ShowMessageBox(const std::wstring& title, const std::wstring& message, UINT type) const
{
	MessageBox(hWnd, message.c_str(), title.c_str(), type);
}

bool MainWindow::ProcessMessage()
{
	MSG msg;
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if (msg.message == WM_QUIT)
		{
			return false;
		}
	}
	return true;
}

void MainWindow::ProcessMouseMove(int xPos, int yPos)
{
	if (xPos> 0 && xPos < ApplicationValues::Instance().ScreenWidth && yPos > 0 && yPos < ApplicationValues::Instance().ScreenHeight)
	{
		Mouse::Instance().OnMouseMove(xPos, yPos);
		if (!Mouse::Instance().IsInWindow())
		{
			Mouse::Instance().OnMouseEnter();
		}
	}
}

void MainWindow::ProcessMouseClick(int xPos, int yPos)
{
	Mouse::Instance().OnLeftPressed(xPos, yPos);
}

void MainWindow::ProcessMouseRelease(int xPos, int yPos)
{
	Mouse::Instance().OnLeftReleased(xPos, yPos);
}

void MainWindow::ProcessKeyPressed(int keyCode)
{
	Keyboard::Instance().OnKeyPressed(keyCode);
}

void MainWindow::ProcessKeyReleased(int keyCode)
{
	Keyboard::Instance().OnKeyReleased(keyCode);
}

LRESULT WINAPI MainWindow::_HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// use create parameter passed in from CreateWindow() to store window class pointer at WinAPI side
	if (msg == WM_NCCREATE)
	{
		// extract ptr to window class from creation data
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		MainWindow* const pWnd = reinterpret_cast<MainWindow*>(pCreate->lpCreateParams);
		// sanity check
		assert(pWnd != nullptr);
		// set WinAPI-managed user data to store ptr to window class
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		// set message proc to normal (non-setup) handler now that setup is finished
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&MainWindow::_HandleMsgThunk));
		// forward message to window class handler
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}
	// if we get a message before the WM_NCCREATE message, handle with default handler
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT WINAPI MainWindow::_HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// retrieve ptr to window class
	MainWindow* const pWnd = reinterpret_cast<MainWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	// forward message to window class handler
	return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}

LRESULT MainWindow::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KILLFOCUS:
		Keyboard::Instance().ClearState();
		break;

		// ************ KEYBOARD MESSAGES ************ //
	case WM_KEYDOWN:
		if (!(lParam & 0x40000000) || Keyboard::Instance().AutorepeatIsEnabled()) // no thank you on the autorepeat
		{
			Keyboard::Instance().OnKeyPressed(static_cast<unsigned char>(wParam));
		}
		break;
	case WM_KEYUP:
		Keyboard::Instance().OnKeyReleased(static_cast<unsigned char>(wParam));
		break;
	case WM_CHAR:
		Keyboard::Instance().OnChar(static_cast<unsigned char>(wParam));
		break;
		// ************ END KEYBOARD MESSAGES ************ //

		// ************ MOUSE MESSAGES ************ //
	case WM_MOUSEMOVE:
	{
		POINTS pt = MAKEPOINTS(lParam);
		if (pt.x > 0 && pt.x < ApplicationValues::Instance().ScreenWidth && pt.y > 0 && pt.y < ApplicationValues::Instance().ScreenHeight)
		{
			Mouse::Instance().OnMouseMove(pt.x, pt.y);
			if (!Mouse::Instance().IsInWindow())
			{
				SetCapture(hWnd);
				Mouse::Instance().OnMouseEnter();
			}
		}
		else
		{
			if (wParam & (MK_LBUTTON | MK_RBUTTON))
			{
				pt.x = std::max(short(0), pt.x);
				pt.x = std::min(short(ApplicationValues::Instance().ScreenHeight - 1), pt.x);
				pt.y = std::max(short(0), pt.y);
				pt.y = std::min(short(ApplicationValues::Instance().ScreenHeight - 1), pt.y);
				Mouse::Instance().OnMouseMove(pt.x, pt.y);
			}
			else
			{
				ReleaseCapture();
				Mouse::Instance().OnMouseLeave();
				Mouse::Instance().OnLeftReleased(pt.x, pt.y);
				Mouse::Instance().OnRightReleased(pt.x, pt.y);
			}
		}
		break;
	}
	case WM_LBUTTONDOWN:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		Mouse::Instance().OnLeftPressed(pt.x, pt.y);
		SetForegroundWindow(hWnd);
		break;
	}
	case WM_RBUTTONDOWN:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		Mouse::Instance().OnRightPressed(pt.x, pt.y);
		break;
	}
	case WM_LBUTTONUP:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		Mouse::Instance().OnLeftReleased(pt.x, pt.y);
		break;
	}
	case WM_RBUTTONUP:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		Mouse::Instance().OnRightReleased(pt.x, pt.y);
		break;
	}
	case WM_MOUSEWHEEL:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
		{
			Mouse::Instance().OnWheelUp(pt.x, pt.y);
		}
		else if (GET_WHEEL_DELTA_WPARAM(wParam) < 0)
		{
			Mouse::Instance().OnWheelDown(pt.x, pt.y);
		}
		break;
	}
	// ************ END MOUSE MESSAGES ************ //
	case WM_DEVICECHANGE:
		if (wParam == DBT_DEVICEARRIVAL)
		{
			auto pDev = reinterpret_cast<PDEV_BROADCAST_HDR>(lParam);
			if (pDev)
			{
				if (pDev->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE)
				{
					auto pInter = reinterpret_cast<
						const PDEV_BROADCAST_DEVICEINTERFACE>(pDev);
					if (pInter->dbcc_classguid == KSCATEGORY_AUDIO)
					{
						Audio::Instance().OnNewAudioDevice();
					}
				}
			}
		}
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}