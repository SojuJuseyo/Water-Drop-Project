#pragma once

#include "Scene.h"
#include "LevelScene.h"

namespace Moo
{
	enum e_menu
	{
		PLAY,
		CONTROLS,
		QUIT
	};

	class Menu : public Scene
	{
	public:
		Menu();
		~Menu();
		bool	init(std::shared_ptr<Moo::Window> window, std::map<std::string, Texture>);
		bool	runUpdate();
		void	clean();

	private:
		e_menu	_offset;
		std::map<std::string, std::shared_ptr<Sprite>> _sprites;
		std::shared_ptr<Moo::Window> _window;
		std::shared_ptr<std::map<std::string, Texture>> _textures;
	};
}
