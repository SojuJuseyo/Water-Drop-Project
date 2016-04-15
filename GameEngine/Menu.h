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
		bool	init(std::shared_ptr<Moo::Window> window);
		bool	runUpdate();
		void	clean();

	private:
		e_menu	_offset;
		Texture *backgroundText;
		Sprite *background;
		Texture *buttonText;
		Sprite *button_play;
		Sprite *button_controls;
		Sprite *button_quit;
		std::shared_ptr<Moo::Window> _window;
	};
}
