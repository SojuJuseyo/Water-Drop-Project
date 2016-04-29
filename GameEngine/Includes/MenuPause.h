#pragma once

#include "Scene.h"
#include "LevelScene.h"

namespace Moo
{
	enum e_menu_pause
	{
		RESUME,
		HOW_TO_PLAY,
		EXIT
	};

	class MenuPause : public Scene
	{
	public:
		MenuPause();
		~MenuPause();
		bool	init(std::shared_ptr<Moo::Window> window);
		bool	runUpdate();
		void	clean();

	private:
		e_menu_pause	_offset;
		std::map<std::string, std::shared_ptr<Texture>> _textures;
		std::map<std::string, std::shared_ptr<Sprite>> _sprites;
		std::shared_ptr<Moo::Window> _window;
	};
}

