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
		_animation = std::make_shared<Moo::Sprite>(800.f, 600.f, 0.f, 0.f, 2, 6, true);
		_animation->loadTexture(&_textures.get()->at("Loading"));
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