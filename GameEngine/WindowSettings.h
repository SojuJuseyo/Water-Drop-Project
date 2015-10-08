#pragma once

#include <string>

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