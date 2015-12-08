#include "Keyboard.h"
#include <iostream>

namespace Moo
{
	void Keyboard::setLastPressed(UINT lastPressed)
	{
		_lastPressed = lastPressed;
	}

	UINT Keyboard::getLastPressed()
	{
		return _lastPressed;
	}

	bool Keyboard::isPressed(Keyboard::Key key)
	{
		SHORT tabKeyState = GetAsyncKeyState(key);
		if ((1 << 16) & tabKeyState) {
			return true;
		}
		return false;
	}
}