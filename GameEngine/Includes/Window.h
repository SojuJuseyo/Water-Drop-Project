#pragma once

#include <iostream>

#include <windows.h>
#include <windowsx.h>
#include <sstream>
#include "WindowSettings.h"
#include "d3d.h"
#include "Fps.h"
#include "Keyboard.h"
#include "Sprite.h"

#define WM_FULLSCREEN WM_USER + 0
#define WM_PAUSEGAME WM_USER + 1
#define WM_UNPAUSEGAME WM_USER + 2
#define WM_CLICK WM_USER + 3

namespace Moo
{
	class Text;

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
		void inCameradraw(Sprite *sprite);
		void inCameradraw(Text *text);
		void display();
		void setFpsLimit(float limit);
		float getFps();

	private:
		WindowSettings _config;
		HWND _hwnd;
		float _fpsLimit;
		ComPtr<ID3D11Device> _dev;
		ComPtr<ID3D11DeviceContext> _devcon;
		d3d _system;
		Fps _fps;
	};
}

static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if ((message == WM_SYSCOMMAND && (wParam & 0xF020) == SC_MINIMIZE) ||
		message == WM_KILLFOCUS) {
		PostMessage(hWnd, WM_PAUSEGAME, 0, 0);
	}
	if (message == WM_SETFOCUS) {
		PostMessage(hWnd, WM_UNPAUSEGAME, 0, 0);
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
