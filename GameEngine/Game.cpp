#include "Game.h"

namespace Moo
{
	Game::Game()
	{
		LevelScene *scene = new LevelScene;
		setScene(scene);
	}

	Game::~Game()
	{
		if (_scene != nullptr) {
			delete(_scene);
		}
	}

	void Game::setScene(Scene *scene)
	{
		if (_scene != nullptr) {
			delete(_scene);
		}
		_scene = scene;
	}

	bool Game::run(Window &window)
	{
		bool state = true;
		while (state) {
			state = _scene->run(window);
		}
		window.destroy();
		return true;
	}
}