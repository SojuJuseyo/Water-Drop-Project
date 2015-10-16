#include "Keyboard.h"

namespace Moo
{
	bool Keyboard::isPressed(Keyboard::Key key)
	{
		if (GetAsyncKeyState(key)) {
			return true;
		}
		return false;
	}
}