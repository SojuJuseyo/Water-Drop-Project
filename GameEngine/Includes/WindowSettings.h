#pragma once

#include <string>
#include "Includes/Vector2f.h"

#define FPS_LIMIT		60

namespace Moo
{
	class WindowSettings
	{
	public:
		WindowSettings() { }
		WindowSettings(const std::string &title, const Vector2f &screenSize);
		~WindowSettings();
		const std::string &getTitle() const { return _title; }
		const Vector2f &getScreenSize() const { return _screenSize; }

	private:
		std::string	_title;
		Vector2f	_screenSize;
	};
}