#pragma once
#include "Window.h"
#include "d3d.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Moo::Window window(hInstance, Moo::WindowSettings("test"));

	while (window.isOpen())
	{
		//window.events();
		window.clear();
		//window.draw();
		window.display();
	}
	window.destroy();
	return 0;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT rcClient;
	POINT ptClientUL;
	POINT ptClientLR;
	static POINTS ptsBegin;

	if (message == WM_LBUTTONDOWN)
	{
		SetCapture(hWnd);
		GetClientRect(hWnd, &rcClient);
		ptClientUL.x = rcClient.left;
		ptClientUL.y = rcClient.top;
		ptClientLR.x = rcClient.right + 1;
		ptClientLR.y = rcClient.bottom + 1;
		ClientToScreen(hWnd, &ptClientUL);
		ClientToScreen(hWnd, &ptClientLR);
		SetRect(&rcClient, ptClientUL.x, ptClientUL.y,
			ptClientLR.x, ptClientLR.y);
		ClipCursor(&rcClient);
		ptsBegin = MAKEPOINTS(lParam);
		PostMessage(hWnd, WM_CLICK, ptsBegin.x, ptsBegin.y);
	}
	if (wParam == VK_ESCAPE) {
		PostQuitMessage(0);
		return 0;
	}
	if (wParam == VK_LEFT) {
		PostMessage(hWnd, WM_LEFT, 0, 0);
	}
	if (wParam == VK_RIGHT) {
		PostMessage(hWnd, WM_RIGHT, 0, 0);
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