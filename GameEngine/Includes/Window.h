#pragma once

#include <iostream>

#include <windows.h>
#include <windowsx.h>
#include <sstream>
#include "../Includes/WindowSettings.h"
#include "../Includes/d3d.h"
#include "../Includes/Fps.h"
#include "../Includes/Keyboard.h"
#include "../Includes/Sprite.h"
#include "../Includes/SpriteRect.h"

#define WM_FULLSCREEN WM_USER + 0
#define WM_LEFT WM_USER + 1
#define WM_RIGHT WM_USER + 2
#define WM_CLICK WM_USER + 3

namespace Moo
{
	class Window
	{
	public:
		Window(HINSTANCE hInstance, WindowSettings &config);
		~Window();

		void initialize(HINSTANCE hInstance);
		bool isOpen();
		void destroy();
		void clear();
		void draw(Drawable * drawable);
		void display();
		void setFpsLimit(float limit);
		float getFps();

	private:
		WindowSettings _config;
		HWND _hwnd;
		float _fpsLimit;
		ID3D11Device *_dev;
		ID3D11DeviceContext *_devcon;
		d3d _system;
	};
}

static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (wParam == VK_ESCAPE) {
		PostQuitMessage(0);
		return 0;
	}
	if (wParam == VK_F1) {
		PostMessage(hWnd, WM_FULLSCREEN, 0, 0);
	}
	if (message == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}
