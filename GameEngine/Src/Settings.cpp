#include "Settings.h"

Settings::Settings(std::map<std::string, std::string> fileContent)
{
	this->fillAttributes(fileContent);
}

Settings::~Settings()
{
}

void	Settings::fillAttributes(std::map<std::string, std::string> fileContent)
{
	for (auto field : fileContent)
	{
		if (field.first == SETTINGS_RESOLUTION)
			this->setResolution(field.second);
		else if (field.first == SETTINGS_VOLUME)
			this->setVolume(field.second);
		else if (field.first == SETTINGS_FULLSCREEN)
			this->setIsFullscreen(field.second);
		else if (field.first == SETTINGS_FPS)
			this->setFps(field.second);
		else if (field.first == SETTINGS_KEYS_MAPPING)
			this->setKeysMapping(field.second);
	}
}

void	Settings::setResolution(std::string resolution)
{
	char* next_token[1] = {};

	char *word = strtok_s(&resolution[0], "x", &next_token[0]);
	if (word == NULL || strlen(word) == resolution.length())
		throw std::string("Invalid resolution: [" + resolution + "]");
	this->_resolution.first = atoi(word);

	word = strtok_s(NULL, "x", &next_token[0]);
	if (word == NULL)
		throw std::string("Invalid resolution: [" + resolution + "]");
	this->_resolution.second = atoi(word);
}

void	Settings::setResolution(std::pair<int, int> resolution)
{
	_resolution = resolution;
}

std::pair<int, int>	Settings::getResolution() const
{
	return _resolution;
}

void	Settings::setVolume(std::string volume)
{
	for (char c : volume)
		if (!isdigit(c))
			throw std::string("Invalid volume, must be contained between 0 and 100 : [" + volume + "]");
	if (std::stoi(volume) < 0 || std::stoi(volume) > 100)
		throw std::string("Invalid volume, must be contained between 0 and 100 : [" + volume + "]");
	this->_volume = std::stoi(volume);
}

void	Settings::setVolume(int volume)
{
	_volume = volume;
}

int		Settings::getVolume() const
{
	return _volume;
}

void	Settings::setIsFullscreen(std::string isFullscreen)
{
	if (isFullscreen != "true" && isFullscreen != "false")
		throw std::string("Invalid isFullscreen, must be true or false : [" + isFullscreen + "]");
	if (isFullscreen == "true")
		this->_isFullscreen = true;
	else
		this->_isFullscreen = false;
}

void	Settings::setIsFullscreen(bool isFullscreen)
{
	this->_isFullscreen = isFullscreen;
}

bool	Settings::getIsFullscreen() const
{
	return this->_isFullscreen;
}

void	Settings::setFps(std::string fps)
{
	for (char c : fps)
		if (!isdigit(c))
			throw std::string("Invalid fps, must be contained between 0 and 100 : [" + fps + "]");
	if (std::stoi(fps) < 0 || std::stoi(fps) > 100)
		throw std::string("Invalid fps, must be contained between 0 and 100 : [" + fps + "]");
	this->_fps = std::stoi(fps);
}

void	Settings::setFps(int fps)
{
	this->_fps = fps;
}

int		Settings::getFps() const
{
	return this->_fps;
}

void	Settings::setKeysMapping(std::string keysMapping)
{
	this->_keysMapping = keysMapping;
}

std::string	Settings::getKeysMapping() const
{
	return this->_keysMapping;
}