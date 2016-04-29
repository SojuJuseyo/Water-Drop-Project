#pragma once

#include "../Includes/Scene.h"
#include "../Includes/LevelScene.h"

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
		bool	init(std::shared_ptr<Moo::Window> window);
		bool	runUpdate();
		void	clean();

	private:
		e_menu	_offset;
		std::map<std::string, std::shared_ptr<Texture>> _textures;
		std::map<std::string, std::shared_ptr<Sprite>> _sprites;
		std::shared_ptr<Moo::Window> _window;
	};
}
