#include "Keyboard.h"
#include <iostream>

namespace Moo
{
	Keyboard::Keyboard()
	{

	}

	bool Keyboard::isDown(Keyboard::Key key)
	{
		for (int i = 0; i < NUM_KEYS; i++)
			if (Keyboard::getInstance()._keyCodes[i] == key &&
				Keyboard::getInstance()._keyStates[i] == (PRESSED | TAPPED))
					return true;
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
		for (int i = 0; i < NUM_KEYS; i++)
			if (Keyboard::getInstance()._keyCodes[i] == key &&
				Keyboard::getInstance()._keyStates[i] != 0)
					return true;
		return false;
	}

	void Keyboard::updateInput()
	{
		Keyboard &keyBoard = Keyboard::getInstance();

		for (int i = 0; i < NUM_KEYS; i++) {
			if (KEYPRESSED(keyBoard._keyCodes[i])) {
				if (0 == keyBoard._keyStates[i])	
					keyBoard._keyStates[i] = PRESSED | TAPPED;
				else			
					keyBoard._keyStates[i] = PRESSED;
			} else {
				if (keyBoard._keyStates[i] && (0 == (KEYUP&keyBoard._keyStates[i])))
					keyBoard._keyStates[i] = KEYUP;
				else
					keyBoard._keyStates[i] = 0;
			}
		}
	}
}