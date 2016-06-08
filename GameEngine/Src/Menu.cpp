#include "Menu.h"

namespace Moo
{
	Menu::Menu()
	{
	}

	Menu::~Menu()
	{
	}

	void	Menu::addSprite(std::string name, std::string filename, float width, float height, float x, float y, float divider)
	{
		_sprites[name] = std::make_shared<Sprite>(width, height, x, y);
		_sprites[name]->loadTexture(&_textures.get()->at(filename));
		_sprites[name]->setX(d3d::getInstance().getScreenSize().x / divider - _sprites[name]->getWidth() / 2);
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

		//Title
		_sprites["Title"] = std::make_shared<Moo::Sprite>(529.f, 153.f, 0.f, d3d::getInstance().getScreenSize().y / 10 * 7);
		_sprites["Title"]->loadTexture(&_textures.get()->at("Menu_Title"));
		_sprites["Title"]->setScale(Vector2f(0.75f, 0.75f));
		_sprites["Title"]->setX(d3d::getInstance().getScreenSize().x / 2.f - _sprites["Title"]->getWidth() / 2);

		//Button Play && Play On
		addSprite("Play", "Menu_Play", 129.f, 43.f, 0.f, d3d::getInstance().getScreenSize().y / 10 * 6, 2);
		addSprite("Play_On", "Menu_Play_On", 161.f, 54.f, 0.f, _sprites["Play"]->getY(), 2);
		_sprites["Play_Current"] = _sprites["Play"];

		//Button HowToPlay && HowToPlay On
		addSprite("HowToPlay", "Menu_HowToPlay", 334.f, 42.f, 0.f, _sprites["Play"]->getY() - _sprites["Play"]->getHeight() - spaceBetweenButtons, 2);
		addSprite("HowToPlay_On", "Menu_HowToPlay_On", 418.f, 53.f, 0.f, _sprites["HowToPlay"]->getY(), 2);
		_sprites["HowToPlay_Current"] = _sprites["HowToPlay"];

		//Button Options && Options On
		addSprite("Options", "Menu_Options", 225.f, 42.f, 0.f, _sprites["HowToPlay"]->getY() - _sprites["HowToPlay"]->getHeight() - spaceBetweenButtons, 2);
		addSprite("Options_On", "Menu_Options_On", 282.f, 53.f, 0.f, _sprites["Options"]->getY(), 2);
		_sprites["Options_Current"] = _sprites["Options"];

		//Button Credits && Credits On
		addSprite("Credits", "Menu_Credits", 225.f, 42.f, 0.f, _sprites["Options"]->getY() - _sprites["Options"]->getHeight() - spaceBetweenButtons, 2);
		addSprite("Credits_On", "Menu_Credits_On", 283.f, 54.f, 0.f, _sprites["Credits"]->getY(), 2);
		_sprites["Credits_Current"] = _sprites["Credits"];

		//Button Quit && Quit On
		addSprite("Quit", "Menu_Quit", 269.f, 49.f, 0.f, _sprites["Credits"]->getY() - _sprites["Credits"]->getHeight() - spaceBetweenButtons, 2);
		addSprite("Quit_On", "Menu_Quit_On", 337.f, 61.f, 0.f, _sprites["Quit"]->getY(), 2);
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
				Game::getInstance().runScene(Game::HOWTOPLAY_MENU, false);
				return true;
				break;
			case e_menu::OPTIONS:
				Game::getInstance().runScene(Game::SETTINGS_MENU, false);
				return true;
				break;
			case e_menu::CREDITS:
				//Game::getInstance().runScene(Game::CREDITS, false);
				return true;
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
			case e_menu::CREDITS:
				_sprites["Credits_Current"] = _sprites["Credits"];
				_sprites["Options_Current"] = _sprites["Options_On"];
				_offset = e_menu::OPTIONS;
				break;
			case e_menu::QUIT:
				_sprites["Quit_Current"] = _sprites["Quit"];
				_sprites["Credits_Current"] = _sprites["Credits_On"];
				_offset = e_menu::CREDITS;
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
				_sprites["Credits_Current"] = _sprites["Credits_On"];
				_offset = e_menu::CREDITS;
				break;
			case e_menu::CREDITS:
				_sprites["Credits_Current"] = _sprites["Credits"];
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
		_window->draw(_sprites["Credits_Current"].get());
		_window->draw(_sprites["Quit_Current"].get());
		_window->display();

		return true;
	}

	void	Menu::clean()
	{

	}
}