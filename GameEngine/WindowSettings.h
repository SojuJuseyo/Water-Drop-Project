#pragma once

#include <string>

#define	WINDOW_HEIGHT	600
#define WINDOW_WIDTH	800
#define FPS_LIMIT		60

namespace Moo
{
	class WindowSettings
	{
	public:
		WindowSettings() { }
		WindowSettings(const std::string &title);
		~WindowSettings();
		const std::string &getTitle() { return _title; }

	private:
		std::string	_title;
	};
}