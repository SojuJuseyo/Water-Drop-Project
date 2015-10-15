#include "Keyboard.h"

namespace Moo
{
	bool Keyboard::isPressed(Keyboard::Key key)
	{
		MSG msg;
		ZeroMemory(&msg, sizeof(MSG));

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == key)
				return true;
			return false;
		}
	}
}