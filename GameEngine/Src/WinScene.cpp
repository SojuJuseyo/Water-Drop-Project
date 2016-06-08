#include "WinScene.h"

namespace Moo
{
	WinScene::WinScene()
	{
		_hasBeenInited = false;
	}

	WinScene::~WinScene()
	{

	}
	bool WinScene::init(std::shared_ptr<Moo::Window> window, std::map<std::string, Texture> textures)
	{
		_window = window;
		_textures = std::make_shared<std::map<std::string, Texture>>(textures);
		_backgroundSprite = std::make_shared<Moo::Sprite>(1280.f, 1080.f, 0.f, 0.f);
		_backgroundSprite->setScale(Vector2f(0.65f, 0.56f));
		_backgroundSprite->loadTexture(&_textures.get()->at("End"));
		_hasBeenInited = true;
		return true;
	}

	bool WinScene::runUpdate()
	{
		if (_endTime.size() == 0)
		{
			std::ostringstream oss;
			oss << static_cast<int>(Game::getInstance()._gameTime->getElapsedSeconds());
			_endTime = oss.str();
		}

		Moo::Keyboard::updateInput();
		_window->clear();
		_window->draw(_backgroundSprite.get());
		_font = std::make_shared<Font>();
		_font->loadFromFile("Font.dds");
		_time = std::make_shared<Text>(_endTime, 3.f, 310.f, 224.f, _font);
		_window->inCameradraw(_time.get());
		_window->display();
		return true;
	}

	void WinScene::clean()
	{
		_endTime.clear();
	}
}