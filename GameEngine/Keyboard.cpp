#include "Keyboard.h"

namespace Moo
{
	bool Keyboard::isPressed(Keyboard::Key key)
	{
		while (GetAsyncKeyState(key)) {
			return true;
		}
		return false;
	}
}