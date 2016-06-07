#pragma once

#include "Scene.h"
#include "LevelScene.h"
#include "Settings.h"

namespace Moo
{
	enum e_settings
	{
		FULLSCREEN,
		MUSIC,
		SOUND_EFFECTS,
		BACK,
		SAVE
	};

	class SettingsScreen : public Scene
	{
	public:
		SettingsScreen();
		~SettingsScreen();
		void	addSprite(std::string, std::string, float, float, float, float, float);
		bool	init(std::shared_ptr<Moo::Window> window, std::map<std::string, Texture>);
		void	saveSettings();
		bool	runUpdate();
		void	clean();

	private:
		e_settings	_offset;
		bool		_fullscreenOn, _musicOn, _soundEffectsOn;
		std::map<std::string, std::shared_ptr<Sprite>> _sprites;
		std::shared_ptr<Moo::Window> _window;
		std::shared_ptr<std::map<std::string, Texture>> _textures;
	};
}

