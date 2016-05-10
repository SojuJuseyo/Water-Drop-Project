#include "ControleScene.h"

namespace Moo
{
	ControleScene::ControleScene()
	{

	}

	ControleScene::~ControleScene()
	{

	}
	bool ControleScene::init(std::shared_ptr<Moo::Window> window, std::map<std::string, Texture> textures)
	{
		_window = window;
		_textures = std::make_shared<std::map<std::string, Texture>>(textures);

		_backgroundSprite = std::make_shared<Moo::Sprite>(1280.f, 1080.f, 0.f, 0.f);
		_backgroundSprite->setScale(Vector2f(0.65f, 0.56f));
		_backgroundSprite->loadTexture(&_textures.get()->at("Background_Controle"));

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