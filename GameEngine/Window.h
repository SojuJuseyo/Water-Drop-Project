#pragma once

#include <iostream>

#include <windows.h>
#include <windowsx.h>
#include "WindowSettings.h"
#include "d3d.h"
#include "RectangleShape.h"

#define WM_FULLSCREEN WM_USER + 0
#define WM_LEFT WM_USER + 1
#define WM_RIGHT WM_USER + 2
#define WM_CLICK WM_USER + 3
#define HITBOX 10

LRESULT CALLBACK WindowProc(HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam);

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
		void display();

	private:
		WindowSettings _config;
		HWND _hwnd;
		std::vector<RectangleShape *> _rectangles;
	};
}
