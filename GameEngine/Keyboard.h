#pragma once
#include <windows.h>
#include <windowsx.h>

#define WM_LEFT WM_USER + 1
#define WM_RIGHT WM_USER + 2

namespace Moo
{
	static class Keyboard
	{
	public:
		enum Key
		{
			Left = WM_LEFT,
			Right = WM_RIGHT,
		};
		static bool isPressed(Keyboard::Key key);
	private:

	};
}