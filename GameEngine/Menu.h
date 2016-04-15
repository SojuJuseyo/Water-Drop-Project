#pragma once
#include "Scene.h"
#include "LevelScene.h"
#include "Audio.h"

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
		bool	init();
		bool	run(Moo::Window &);
		void	clean();

	private:
		std::shared_ptr<SoundSystem> soundSystem;
		e_menu	_offset;
		Texture *backgroundText;
		Sprite *background;
		Texture *buttonText;
		Sprite *button_play;
		Sprite *button_controls;
		Sprite *button_quit;
	};
}
