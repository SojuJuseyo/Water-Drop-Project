#include "Game.h"

namespace Moo
{
	Game::Game()
	{
		menu = new Menu;
		level = new LevelScene;
		pause = new MenuPause;
		controle = new ControleScene;
	}

	Game::~Game()
	{

	}

	void	Game::initScenes()
	{
		if (!Moo::Audio::getInstance().init()) {
			std::cout << "audio failed" << std::endl;
		}
		menu->init();
		level->init();
		pause->init();
		controle->init();
	}

	void	Game::setExit(bool value)
	{
		_exit = value;
	}

	bool	Game::runScene(TypeScene type, TypeScene lastType, Window &window)
	{
		bool state = true;
		while (state) {
			Moo::d3d::getInstance().getCamera()->reset();
			if (_exit) {
				return false;
			}
			switch (type) {
			case TypeScene::MENU:
				state = menu->run(window);
				break;
			case TypeScene::LEVEL:
				state = level->run(window);
				break;
			case TypeScene::PAUSE:
				state = pause->run(window);
				break;
			case TypeScene::CONTROLE:
				state = controle->run(window);
				break;
			default:
				state = false;
				break;
			}
		}
		switch (lastType) {
		case TypeScene::MENU:
			state = menu->run(window);
			break;
		case TypeScene::LEVEL:
			state = level->run(window);
			break;
		case TypeScene::PAUSE:
			state = menu->run(window);
			break;
		case TypeScene::CONTROLE:
			state = controle->run(window);
			break;
		default:
			state = false;
			break;
		}
		return state;
	}

	bool Game::run(Window &window)
	{
		return runScene(TypeScene::MENU, TypeScene::EXIT, window);
	}
}