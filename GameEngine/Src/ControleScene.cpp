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
		_backgroundTexture = std::make_shared<Texture>();
		_backgroundTexture->loadFromFile(GRAPHICS_PATH + std::string("controle.dds"));
		_backgroundSprite = std::make_shared<Moo::Sprite>(1280.f, 1080.f, 0.f, 0.f);
		_backgroundSprite->setScale(Vector2f(0.65f, 0.56f));
		_backgroundSprite->loadTexture(_backgroundTexture.get());
		return true;
	}

	bool ControleScene::runUpdate()
	{
		Moo::Keyboard::updateInput();
		_window->clear();
		_window->draw(_backgroundSprite.get());
		_window->display();
		return true;
	}

	void ControleScene::clean()
	{
	}
}