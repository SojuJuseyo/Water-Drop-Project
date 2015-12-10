#pragma once

#include "window.h"
#include "Keyboard.h"
#include "Scene.h"
#include "LevelScene.h"
#include "Menu.h"

namespace Moo
{
	class Game
	{
	public:
		Game();
		~Game();
		static Game& getInstance()
		{
			static Game instance;
			return instance;
		}

		bool run(Moo::Window &);
		void setScene(Scene *);

		bool runScene(Scene * scene, Window & window);

	private:
		Scene *_scene;
		Scene *_level;
		Scene *_menu;
	};
}