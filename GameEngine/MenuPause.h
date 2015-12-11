#pragma once
#include "Scene.h"
#include "LevelScene.h"

namespace Moo
{
	enum e_menu_pause
	{
		RESUME,
		CONTROLS,
		QUIT
	};

	class MenuPause : public Scene
	{
	public:
		MenuPause();
		~MenuPause();
		bool	run(Moo::Window &);
		void	clean();

	private:
		e_menu_pause	_offset;
	};
}

