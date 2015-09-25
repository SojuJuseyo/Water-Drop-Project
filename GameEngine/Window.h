#pragma once

#include <iostream>

#include <windows.h>
#include <windowsx.h>
#include <string>

LRESULT CALLBACK WindowProc(HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam);

namespace Moo 
{
	class WindowSettings
	{
	public:
		WindowSettings() { }
		WindowSettings(const std::string &title);
		~WindowSettings();

	private:
		std::string	_title;
	};

	WindowSettings::WindowSettings(const std::string &title)
	{
		_title = title;
	}

	WindowSettings::~WindowSettings()
	{
	}

	class Window
	{
	public:
		Window(HINSTANCE hInstance, WindowSettings &config);
		~Window();

		void initialize(HINSTANCE hInstance);
		void open();
		void destroy();

	private:
		WindowSettings _config;
		HWND _hwnd;
	};

	Window::Window(HINSTANCE hInstance, WindowSettings &config)
	{
		_config = config;
		initialize(hInstance);
	}

	void	Window::initialize(HINSTANCE hInstance)
	{
		WNDCLASSEX wc;
		int posX, posY;
		auto hinstance = GetModuleHandle(NULL);
		auto applicationName = "Engine";

		// Setup the windows class with default settings.
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wc.lpfnWndProc = WindowProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hinstance;
		wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
		wc.hIconSm = wc.hIcon;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = applicationName;
		wc.cbSize = sizeof(WNDCLASSEX);

		RegisterClassEx(&wc);

		auto screenWidth = GetSystemMetrics(SM_CXSCREEN);
		auto screenHeight = GetSystemMetrics(SM_CYSCREEN);

		screenWidth = 800;
		screenHeight = 600;

		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;

		_hwnd = CreateWindowEx(WS_EX_APPWINDOW, applicationName, applicationName,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		posX, posY, screenWidth, screenHeight, NULL, NULL, hinstance, NULL);

		ShowWindow(_hwnd, SW_SHOW);
		SetForegroundWindow(_hwnd);
		SetFocus(_hwnd);
		ShowCursor(false);
		return;
	}

	void	Window::open()
	{
		MSG msg;
		bool done, result;

		ZeroMemory(&msg, sizeof(MSG));

		done = false;
		while (!done)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			if (msg.message == WM_QUIT)
			{
				done = true;
			}
		}
		return;
	}

	void	Window::destroy()
	{
		ShowCursor(true);
		DestroyWindow(_hwnd);
		_hwnd = NULL;
		return;
	}

	Window::~Window()
	{
		destroy();
	}
}


LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}