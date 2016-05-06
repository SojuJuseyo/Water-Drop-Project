#pragma once

#include <string>
#include <map>
#include "Keyboard.h"

// Settings related field names & attributes
#define SETTINGS_RESOLUTION		"resolution"
#define SETTINGS_KEYS_MAPPING	"keys_mapping"
#define SETTINGS_VOLUME			"volume"
#define SETTINGS_FULLSCREEN		"fullscreen"
#define SETTINGS_FPS			"fps"

namespace Moo
{
	class Settings
	{
	public:
		Settings(Settings&);
		Settings(std::map<std::string, std::string>);
		~Settings();

		void	fillAttributes(std::map<std::string, std::string>);

		void					setResolution(std::string);
		void					setResolution(std::pair<int, int>);
		std::pair<int, int>		getResolution() const;
		std::string				getResolutionString() const;

		void					setVolume(std::string);
		void					setVolume(int);
		int						getVolume() const;
		std::string				getVolumeString() const;

		void					setIsFullscreen(std::string);
		void					setIsFullscreen(bool);
		bool					getIsFullscreen() const;
		std::string				getIsFullscreenString() const;

		void					setFps(std::string);
		void					setFps(int);
		int						getFps() const;
		std::string				getFpsString() const;

		void									setKeysMapping(std::map<Keyboard::Key, std::string>);
		std::map<Keyboard::Key, std::string>	getKeysMapping() const;

	private:
		std::pair<int, int>						_resolution;
		std::string								_resolutionString;
		int										_volume;
		std::string								_volumeString;
		bool									_isFullscreen;
		std::string								_isFullsreenString;
		int										_fps;
		std::string								_fpsString;
		std::map<Keyboard::Key, std::string>	_keysMapping;
	};
}
