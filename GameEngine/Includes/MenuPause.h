#pragma once

#include "../Includes/Scene.h"
#include "../Includes/LevelScene.h"

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
		Texture *backgroundText;
		Sprite *background;
		Texture *buttonText;
		Sprite *button_resume;
		Sprite *button_controls;
		Sprite *button_quit;
		std::shared_ptr<Moo::Window> _window;
	};
}

