#pragma once
#include <windows.h>
#include <windowsx.h>
#include "Fps.h"

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
			Shot = 'F',
			A = 'A',
		};
		static Keyboard& getInstance()
		{
			static Keyboard instance;
			return instance;
		}
		void setLastPressed(UINT);
		UINT getLastPressed();
		static bool isPressed(Keyboard::Key key);
	private:
		UINT _lastPressed;
	};
}