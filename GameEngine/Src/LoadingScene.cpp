#include "LoadingScene.h"

namespace Moo
{
	LoadingScene::LoadingScene()
	{
		_hasBeenInited = false;
	}

	LoadingScene::~LoadingScene()
	{

	}
	bool LoadingScene::init(std::shared_ptr<Moo::Window> window, std::map<std::string, Texture> textures)
	{
		_window = window;
		_textures = std::make_shared<std::map<std::string, Texture>>(textures);
		_animation = std::make_shared<Moo::Sprite>(800.f, 600.f, 0.f, 0.f, 1.f, 6, 2);
		_animation->loadTexture(&_textures.get()->at("Loading"));
		_animation->setRectFromSpriteSheet(Moo::Vector2f(0, 0), Moo::Vector2f(800.f, 600.f));
		_hasBeenInited = true;
		return true;
	}

	bool LoadingScene::runUpdate()
	{
		_window->clear();
		_window->draw(_animation.get());
		_window->display();
		return true;
	}

	void LoadingScene::clean()
	{
	}
}