#pragma once

#include <windows.h>
#include <windowsx.h>
#include "Fps.h"

#define NUM_KEYS 13
#define KEYPRESSED(key)		(((GetAsyncKeyState(key) & 0x8000)) ? 1 : 0)
#define PRESSED					0x01
#define TAPPED				0x04
#define KEYUP					0x08

namespace Moo
{
	class Keyboard
	{
	public:
		Keyboard::Keyboard();
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
		static void updateInput();

	private:
		UINT _lastKey;
		int _keyCodes[NUM_KEYS] = {
			VK_LEFT,
			VK_RIGHT,
			VK_SPACE,
			VK_UP,
			VK_DOWN,
			VK_RETURN,
			'F',
			'A',
			'B',
			'C',
			'G',
			VK_ADD,
			VK_SUBTRACT };
		int _keyStates[NUM_KEYS] = { 0 };
	};
}