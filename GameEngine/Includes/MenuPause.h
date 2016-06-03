#pragma once

#include "Scene.h"
#include "LevelScene.h"

namespace Moo
{
	enum e_menu_pause
	{
		RESUME,
		HOW_TO_PLAY_PAUSE,
		EXIT
	};

	class MenuPause : public Scene
	{
	public:
		MenuPause();
		~MenuPause();
		bool	init(std::shared_ptr<Moo::Window> window, std::map<std::string, Texture>);
		bool	runUpdate();
		void	clean();

	private:
		e_menu_pause	_offset;
		std::map<std::string, std::shared_ptr<Sprite>> _sprites;
		std::shared_ptr<Moo::Window> _window;
		std::shared_ptr<std::map<std::string, Texture>> _textures;
	};
}

