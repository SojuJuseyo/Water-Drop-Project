#pragma once
#include <windows.h>
#include <windowsx.h>

namespace Moo
{
	class Keyboard
	{
	public:
		enum Key
		{
			Left = VK_LEFT,
			Right = VK_RIGHT,
			Space = VK_SPACE,
			Up = VK_UP
		};
		static bool isPressed(Keyboard::Key key);
	private:

	};
}