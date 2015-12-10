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
			Down = VK_DOWN,
			Enter = VK_RETURN,
			Shot = 'F',
			A = 'A',
			B = 'B',
			C = 'C',
			GodMode = 'G',
			SizeUp = VK_ADD,
			SizeDown = VK_SUBTRACT,
		};

		static Keyboard& Keyboard::getInstance()
		{
			static Keyboard instance;
			return instance;
		}
		void setLastKey(UINT);
		UINT getLastKey();
		static bool isPressed(Keyboard::Key key);
		void release();
		static bool isDown(Keyboard::Key key);
	private:
		UINT _lastKey;
	};
}