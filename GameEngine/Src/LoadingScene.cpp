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
		_backgroundSprite = std::make_shared<Moo::Sprite>(800.f, 600.f, 0.f, 0.f);
		_backgroundSprite->loadTexture(&_textures.get()->at("Background_Controle"));
		_hasBeenInited = true;
		return true;
	}

	bool LoadingScene::runUpdate()
	{
		_window->clear();
		_window->draw(_backgroundSprite.get());
		_window->display();
		return true;
	}

	void LoadingScene::clean()
	{
	}
}