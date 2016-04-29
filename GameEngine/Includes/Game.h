#pragma once

#include <iostream>
#include <vector>
#include "window.h"
#include "Keyboard.h"
#include "Scene.h"
#include "LevelScene.h"
#include "MenuPause.h"
#include "Menu.h"
#include "ControleScene.h"
#include "SoundSystem.h"
#include "LoadingScene.h"

#define WINDOW_WIDTH 800.f
#define WINDOW_HEIGHT 600.f

namespace Moo
{
	class Game
	{
	public:
		enum e_scene {
			LOADING,
			MAIN_MENU,
			PAUSE_MENU,
			CONTROLS_MENU,
			LEVEL1,
			LEVEL2,
			LEVEL3,
			NUMBER_OF_SCENE
		};
		struct s_scene
		{
			e_scene						sceneType;
			Scene*						scene = nullptr;
			struct s_scene				*prevScene;
		};

		static Game&					getInstance();
		void							startGame(std::shared_ptr<Moo::Window> theUsedWindow);		// a appeller une fois au lancement du programme, il load tout les niveaux, les init et commence automatiquement a run le main menu
		void							runScene(e_scene);											// lance tel ou tel scene directement
		void							backToPrevScene();											// remet bien la scene precedente (si c'etait un niveau de jeu, ca met le jeu en pause; si c'etait la page des controls ca renvoit au menu principal si le jeu etait pas lance et sinon au menu pause)
		void							goToNextScene();											// a utiliser a la fin des menu in game qui permet directment de passer au niveau suivant
		void							exit();														// sert a quitter le jeu
		void							cleanCurrentScene();										// clean la scene actuel
		void							resetAllScenes();											// reset (init) toutes les scenes
		std::shared_ptr<SoundSystem>	getSoundSystem();

	private:
		Game();
		~Game();

		bool							update();
		void							createScene(e_scene, Scene*);
		void							displayLoadingScreen();
		s_scene*						getSceneByType(e_scene sceneType);

		std::vector<s_scene>			_listOfScenes;
		std::shared_ptr<Moo::Window>	_window;
		std::shared_ptr<SoundSystem>	_soundSystem;

		s_scene*						_currentScene = nullptr;
		bool							_isGameRunning = false;
		bool							_isInGame = false;
	};
}