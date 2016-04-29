#include "../Includes/WindowSettings.h"

namespace Moo
{
	WindowSettings::WindowSettings(const std::string &title, const Vector2f &screenSize)
	{
		_title = title;
		_screenSize = screenSize;
	}

	WindowSettings::~WindowSettings()
	{
	}
}