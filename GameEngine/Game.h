#pragma once

#include "window.h"
#include "Keyboard.h"
#include "Scene.h"
#include "LevelScene.h"
#include "MenuPause.h"
#include "Menu.h"
#include "ControleScene.h"
#include "Audio.h"
#include "SoundSystem.h"

#define WINDOW_WIDTH 800.f
#define WINDOW_HEIGHT 600.f

namespace Moo
{
	class Game
	{
	public:
		Game();
		~Game();
		void initScenes();
		static Game& getInstance()
		{
			static Game instance;
			return instance;
		}
		void setExit(bool);
		bool run(Moo::Window &);
		bool runScene(Moo::TypeScene, Moo::TypeScene, Window &);
		std::shared_ptr<SoundSystem> getSoundSystem();

	private:
		Scene *menu;
		Scene *level;
		Scene *controle;
		Scene *pause;
		std::shared_ptr<SoundSystem> soundSystem;
		bool _exit;
	};
}