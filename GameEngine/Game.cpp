#include "Game.h"

namespace Moo
{
	Game::Game()
	{
		_menu = new Menu;
		_level = new LevelScene;
		_scene = _menu;
	}

	Game::~Game()
	{
		if (_scene != nullptr) {
			delete(_scene);
		}
	}

	void Game::setScene(Scene *scene)
	{
		std::cout << "slt" << std::endl;
		//if (_scene != nullptr) {
		//	delete(_scene);
		//}
		_scene = nullptr;
		_scene = scene;
	}
	
	bool Game::runScene(Scene *scene, Window &window)
	{
		bool state = true;

		while (state) {
			state = scene->run(window);
		}
		scene->clean();
		return state;
	}

	bool Game::run(Window &window)
	{
		return runScene(new Menu, window);
	}
}