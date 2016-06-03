#include "Menu.h"

namespace Moo
{
	Menu::Menu()
	{
	}

	Menu::~Menu()
	{
	}

	bool Menu::init(std::shared_ptr<Moo::Window> window, std::map<std::string, Texture> textures)
	{
		_window = window;
		_textures = std::make_shared<std::map<std::string, Texture>>(textures);

		//background
		_sprites["Background"] = std::make_shared<Moo::Sprite>(800.f, 600.f, 0.f, 0.f);
		_sprites["Background"]->loadTexture(&_textures.get()->at("Menu_Background"));

		//Buttons attributes
		float spaceBetweenButtons = 30;
		float middleOfScreen = d3d::getInstance().getScreenSize().x / 2.f;

		//Title
		_sprites["Title"] = std::make_shared<Moo::Sprite>(529.f, 153.f, 0.f, d3d::getInstance().getScreenSize().y / 10 * 7);
		_sprites["Title"]->loadTexture(&_textures.get()->at("Menu_Title"));
		_sprites["Title"]->setScale(Vector2f(0.75f, 0.75f));
		_sprites["Title"]->setX(middleOfScreen - _sprites["Title"]->getWidth() / 2);

		//Button Play && Play On
		_sprites["Play"] = std::make_shared<Sprite>(129.f, 43.f, 0.f, d3d::getInstance().getScreenSize().y / 10 * 5);
		_sprites["Play"]->loadTexture(&_textures.get()->at("Menu_Play"));
		_sprites["Play"]->setX(middleOfScreen - _sprites["Play"]->getWidth() / 2);

		_sprites["Play_On"] = std::make_shared<Sprite>(161.f, 54.f, 0.f, d3d::getInstance().getScreenSize().y / 10 * 5);
		_sprites["Play_On"]->loadTexture(&_textures.get()->at("Menu_Play_On"));
		_sprites["Play_On"]->setX(middleOfScreen - _sprites["Play_On"]->getWidth() / 2);

		_sprites["Play_Current"] = _sprites["Play"];

		//Button HowToPlay && HowToPlay On
		_sprites["HowToPlay"] = std::make_shared<Sprite>(334.f, 42.f, 0.f, _sprites["Play"]->getY() - _sprites["Play"]->getHeight() - spaceBetweenButtons);
		_sprites["HowToPlay"]->loadTexture(&_textures.get()->at("Menu_HowToPlay"));
		_sprites["HowToPlay"]->setX(middleOfScreen - _sprites["HowToPlay"]->getWidth() / 2);

		_sprites["HowToPlay_On"] = std::make_shared<Sprite>(418.f, 53.f, 0.f, _sprites["Play"]->getY() - _sprites["Play"]->getHeight() - spaceBetweenButtons);
		_sprites["HowToPlay_On"]->loadTexture(&_textures.get()->at("Menu_HowToPlay_On"));
		_sprites["HowToPlay_On"]->setX(middleOfScreen - _sprites["HowToPlay_On"]->getWidth() / 2);

		_sprites["HowToPlay_Current"] = _sprites["HowToPlay"];

		//Button Options && Options On
		_sprites["Options"] = std::make_shared<Sprite>(225.f, 42.f, 0.f, _sprites["HowToPlay"]->getY() - _sprites["HowToPlay"]->getHeight() - spaceBetweenButtons);
		_sprites["Options"]->loadTexture(&_textures.get()->at("Menu_Options"));
		_sprites["Options"]->setX(middleOfScreen - _sprites["Options"]->getWidth() / 2);

		_sprites["Options_On"] = std::make_shared<Sprite>(282.f, 53.f, 0.f, _sprites["HowToPlay"]->getY() - _sprites["HowToPlay"]->getHeight() - spaceBetweenButtons);
		_sprites["Options_On"]->loadTexture(&_textures.get()->at("Menu_Options_On"));
		_sprites["Options_On"]->setX(middleOfScreen - _sprites["Options_On"]->getWidth() / 2);

		_sprites["Options_Current"] = _sprites["Options"];

		//Button Quit && Quit On
		_sprites["Quit"] = std::make_shared<Sprite>(129.f, 49.f, 0.f, _sprites["Options"]->getY() - _sprites["Options"]->getHeight() - spaceBetweenButtons);
		_sprites["Quit"]->loadTexture(&_textures.get()->at("Menu_Quit"));
		_sprites["Quit"]->setX(middleOfScreen - _sprites["Quit"]->getWidth() / 2);

		_sprites["Quit_On"] = std::make_shared<Sprite>(162.f, 61.f, 0.f, _sprites["Options"]->getY() - _sprites["Options"]->getHeight() - spaceBetweenButtons);
		_sprites["Quit_On"]->loadTexture(&_textures.get()->at("Menu_Quit_On"));
		_sprites["Quit_On"]->setX(middleOfScreen - _sprites["Quit_On"]->getWidth() / 2);

		_sprites["Quit_Current"] = _sprites["Quit"];

		_offset = e_menu::PLAY;
		_sprites["Play_Current"] = _sprites["Play_On"];
		return true;
	}


	bool Menu::runUpdate()
	{
		Moo::Keyboard::updateInput();

		if (Moo::Keyboard::isDown(Keyboard::Enter))
			switch (_offset)
			{
			case e_menu::PLAY:
				Game::getInstance().runScene(Game::LEVEL, false);
				return true;
				break;
			case e_menu::HOW_TO_PLAY:
				Game::getInstance().runScene(Game::CONTROLS_MENU, false);
				return true;
				break;
			case e_menu::OPTIONS:
				break;
			case e_menu::QUIT:
				return false;
				break;
			}

		if (Keyboard::isDown(Keyboard::Up))
		{
			Game::getInstance().getSoundSystem()->playSound("Menu", false);
			switch (_offset)
			{
			case e_menu::PLAY:
				_sprites["Play_Current"] = _sprites["Play"];
				_sprites["Quit_Current"] = _sprites["Quit_On"];
				_offset = e_menu::QUIT;
				break;
			case e_menu::HOW_TO_PLAY:
				_sprites["HowToPlay_Current"] = _sprites["HowToPlay"];
				_sprites["Play_Current"] = _sprites["Play_On"];
				_offset = e_menu::PLAY;
				break;
			case e_menu::OPTIONS:
				_sprites["Options_Current"] = _sprites["Options"];
				_sprites["HowToPlay_Current"] = _sprites["HowToPlay_On"];
				_offset = e_menu::HOW_TO_PLAY;
				break;
			case e_menu::QUIT:
				_sprites["Quit_Current"] = _sprites["Quit"];
				_sprites["Options_Current"] = _sprites["Options_On"];
				_offset = e_menu::OPTIONS;
				break;
			}
		}
		else if (Keyboard::isDown(Keyboard::Down))
		{
			Game::getInstance().getSoundSystem()->playSound("Menu", false);
			switch (_offset)
			{
			case e_menu::PLAY:
				_sprites["Play_Current"] = _sprites["Play"];
				_sprites["HowToPlay_Current"] = _sprites["HowToPlay_On"];
				_offset = e_menu::HOW_TO_PLAY;
				break;
			case e_menu::HOW_TO_PLAY:
				_sprites["HowToPlay_Current"] = _sprites["HowToPlay"];
				_sprites["Options_Current"] = _sprites["Options_On"];
				_offset = e_menu::OPTIONS;
				break;
			case e_menu::OPTIONS:
				_sprites["Options_Current"] = _sprites["Options"];
				_sprites["Quit_Current"] = _sprites["Quit_On"];
				_offset = e_menu::QUIT;
				break;
			case e_menu::QUIT:
				_sprites["Quit_Current"] = _sprites["Quit"];
				_sprites["Play_Current"] = _sprites["Play_On"];
				_offset = e_menu::PLAY;
				break;
			}
		}

		_window->clear();
		_window->draw(_sprites["Background"].get());
		_window->draw(_sprites["Title"].get());
		_window->draw(_sprites["Play_Current"].get());
		_window->draw(_sprites["HowToPlay_Current"].get());
		_window->draw(_sprites["Options_Current"].get());
		_window->draw(_sprites["Quit_Current"].get());
		_window->display();

		return true;
	}

	void	Menu::clean()
	{

	}
}