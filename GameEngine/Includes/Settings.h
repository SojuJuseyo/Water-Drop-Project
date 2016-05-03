#pragma once

#include <string>
#include <map>
#include "JsonParser.h"

class Settings
{
public:
	Settings(std::map<std::string, std::string>);
	~Settings();

	void	fillAttributes(std::map<std::string, std::string>);

	void					setResolution(std::string);
	void					setResolution(std::pair<int, int>);
	std::pair<int, int>		getResolution() const;

	void					setVolume(std::string);
	void					setVolume(int);
	int						getVolume() const;

	void					setIsFullscreen(std::string);
	void					setIsFullscreen(bool);
	bool					getIsFullscreen() const;

	void					setFps(std::string);
	void					setFps(int);
	int						getFps() const;

	void					setKeysMapping(std::string);
	std::string				getKeysMapping() const;

private:
	std::pair<int, int>		_resolution;
	int						_volume;
	bool					_isFullscreen;
	int						_fps;
	std::string				_keysMapping;
};

