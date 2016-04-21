#include "Keyboard.h"
#include <iostream>

namespace Moo
{
	bool Keyboard::isDown(Keyboard::Key key)
	{
		if ((Fps::getInstance().getTick() % 25) == 0) {
			Keyboard::getInstance().release();
		}
		if (Keyboard::getInstance().getLastKey() == key) {
			return false;
		}
		if ((GetAsyncKeyState(key)) < 0) {
			Keyboard::getInstance().setLastKey(key);
			return true;
		}
		return false;
	}

	void Keyboard::release()
	{
		Keyboard::getInstance().setLastKey(0);
	}

	void Keyboard::setLastKey(UINT lastKey)
	{
		_lastKey = lastKey;
	}

	UINT Keyboard::getLastKey()
	{
		return _lastKey;
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