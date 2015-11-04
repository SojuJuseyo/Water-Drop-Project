#pragma once

#include <iostream>

#include <windows.h>
#include <windowsx.h>
#include "WindowSettings.h"
#include "d3d.h"
#include "Fps.h"
#include "RectangleShape.h"
#include "Sprite.h"

#define WM_FULLSCREEN WM_USER + 0
#define WM_LEFT WM_USER + 1
#define WM_RIGHT WM_USER + 2
#define WM_CLICK WM_USER + 3
#define HITBOX 10

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
		void draw(Shape * shape);
		void draw(Sprite * sprite);
		void display();
		void setFpsLimit(float limit);
		float getFps();

	private:
		WindowSettings _config;
		HWND _hwnd;
		std::vector<RectangleShape *> _rectangles;
		float _fpsLimit;
		Fps _fps;
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