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
		bool	run(Moo::Window &);
		void	clean();

	private:
		e_menu	_offset;
	};
}
