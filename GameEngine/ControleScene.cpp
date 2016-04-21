#include "ControleScene.h"

namespace Moo
{
	ControleScene::ControleScene()
	{

	}

	ControleScene::~ControleScene()
	{

	}
	bool ControleScene::init(std::shared_ptr<Moo::Window> window)
	{
		_window = window;
		controleText = new Moo::Texture;
		controleText->loadFromFile("controle.dds");
		controle = new Moo::Sprite(1280, 1080, 0, 0);
		controle->setScale(Vector2f(0.65f, 0.56f));
		controle->loadTexture(controleText);
		return true;
	}

	bool ControleScene::runUpdate()
	{
		_window->clear();
		_window->draw(controle);
		_window->display();
		return true;
	}

	void ControleScene::clean()
	{
	}
}