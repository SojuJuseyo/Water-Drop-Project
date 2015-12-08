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
			Up = VK_UP,
			// Temp. Replace it with a key like F when working
			Shot = VK_NUMPAD0,
		};
		static bool isPressed(Keyboard::Key key);
	private:

	};
}