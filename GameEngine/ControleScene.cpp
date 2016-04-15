#include "ControleScene.h"

namespace Moo
{
	ControleScene::ControleScene()
	{

	}

	ControleScene::~ControleScene()
	{

	}
	bool ControleScene::init()
	{
		controleText = new Moo::Texture;
		controleText->loadFromFile("controle.dds");
		controle = new Moo::Sprite(1280, 1080, 0, 0);
		controle->setScale(Vector2f(0.65f, 0.56f));
		controle->loadTexture(controleText);
		
		//init sound system
		this->soundSystem = Game::getInstance().getSoundSystem();

		return false;
	}

	bool ControleScene::run(Moo::Window & window)
	{
		while (window.isOpen())
		{
			window.clear();
			window.draw(controle);
			window.display();
		}
		return false;
	}

	void ControleScene::clean()
	{
	}
}