#pragma once

#include "Scene.h"
#include "LevelScene.h"
#include "Audio.h"

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
		bool	run(Moo::Window &);
		bool	init();
		void	clean();

	private:
		std::shared_ptr<SoundSystem> soundSystem;
		e_menu_pause	_offset;
		Texture *backgroundText;
		Sprite *background;
		Texture *buttonText;
		Sprite *button_resume;
		Sprite *button_controls;
		Sprite *button_quit;
	};
}

