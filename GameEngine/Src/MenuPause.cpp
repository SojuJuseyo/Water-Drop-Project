#include "MenuPause.h"

namespace Moo
{
	MenuPause::MenuPause()
	{
	}


	MenuPause::~MenuPause()
	{
	}

	void	MenuPause::addSprite(std::string name, std::string filename, float width, float height, float x, float y, float divider)
	{
		_sprites[name] = std::make_shared<Sprite>(width, height, x, y);
		_sprites[name]->loadTexture(&_textures.get()->at(filename));
		_sprites[name]->setX(d3d::getInstance().getScreenSize().x / divider - _sprites[name]->getWidth() / 2);
	}

	bool MenuPause::init(std::shared_ptr<Moo::Window> window, std::map<std::string, Texture> textures)
	{
		_window = window;
		_textures = std::make_shared<std::map<std::string, Texture>>(textures);

		//background
		_sprites["Background"] = std::make_shared<Moo::Sprite>(800.f, 600.f, 0.f, 0.f);
		_sprites["Background"]->loadTexture(&_textures.get()->at("Menu_Background"));

		//Buttons attributes
		float spaceBetweenButtons = 30;

		//Title
		addSprite("Pause", "Pause_Menu_Title", 274.f, 55.f, 0.f, d3d::getInstance().getScreenSize().y / 10 * 8, 2);

		//Button Resume && Resume On
		addSprite("Resume", "Pause_Menu_Resume", 243.f, 54.f, 0.f, d3d::getInstance().getScreenSize().y / 10 * 6, 2);
		addSprite("Resume_On", "Pause_Menu_Resume_On", 243.f, 54.f, 0.f, d3d::getInstance().getScreenSize().y / 10 * 6, 2);
		_sprites["Resume_Current"] = _sprites["Resume"];

		//Button HowToPlay && HowToPlay On
		addSprite("HowToPlay", "Menu_HowToPlay", 334.f, 42.f, 0.f, _sprites["Resume"]->getY() - _sprites["Resume"]->getHeight() - spaceBetweenButtons, 2);
		addSprite("HowToPlay_On", "Menu_HowToPlay_On", 418.f, 53.f, 0.f, _sprites["HowToPlay"]->getY(), 2);
		_sprites["HowToPlay_Current"] = _sprites["HowToPlay"];

		//Button Options && Options On
		addSprite("Options", "Menu_Options", 225.f, 42.f, 0.f, _sprites["HowToPlay"]->getY() - _sprites["HowToPlay"]->getHeight() - spaceBetweenButtons, 2);
		addSprite("Options_On", "Menu_Options_On", 282.f, 53.f, 0.f, _sprites["Options"]->getY(), 2);
		_sprites["Options_Current"] = _sprites["Options"];

		//Button Quit && Quit On
		addSprite("Quit", "Menu_Quit", 129.f, 49.f, 0.f, _sprites["Options"]->getY() - _sprites["Options"]->getHeight() - spaceBetweenButtons, 2);
		addSprite("Quit_On", "Menu_Quit_On", 162.f, 61.f, 0.f, _sprites["Quit"]->getY(), 2);
		_sprites["Quit_Current"] = _sprites["Quit"];

		_offset = e_menu_pause::RESUME;
		_sprites["Resume_Current"] = _sprites["Resume_On"];
		return true;
	}

	bool MenuPause::runUpdate()
	{
		Moo::Keyboard::updateInput();

		if (Moo::Keyboard::isDown(Keyboard::Enter))
		{
			switch (_offset)
			{
			case e_menu_pause::RESUME:
				Game::getInstance().backToPrevScene();
				return true;
				break;
			case e_menu_pause::HOW_TO_PLAY_PAUSE:
				Game::getInstance().runScene(Game::HOWTOPLAY_MENU, false);
				return true;
				break;
			case e_menu_pause::SETTINGS_PAUSE:
				Game::getInstance().runScene(Game::SETTINGS_MENU, false);
				return true;
				break;
			case e_menu_pause::EXIT:
				Game::getInstance().runScene(Game::MAIN_MENU, false);
				return true;
				break;
			}
		}
		else if (Keyboard::isDown(Keyboard::Up))
		{
			Game::getInstance().getSoundSystem()->playSound("Menu", false);
			switch (_offset)
			{
			case e_menu_pause::RESUME:
				_sprites["Resume_Current"] = _sprites["Resume"];
				_sprites["Quit_Current"] = _sprites["Quit_On"];
				_offset = e_menu_pause::EXIT;
				break;
			case e_menu_pause::HOW_TO_PLAY_PAUSE:
				_sprites["HowToPlay_Current"] = _sprites["HowToPlay"];
				_sprites["Resume_Current"] = _sprites["Resume_On"];
				_offset = e_menu_pause::RESUME;
				break;
			case e_menu_pause::SETTINGS_PAUSE:
				_sprites["Options_Current"] = _sprites["Options"];
				_sprites["HowToPlay_Current"] = _sprites["HowToPlay_On"];
				_offset = e_menu_pause::HOW_TO_PLAY_PAUSE;
				break;
			case e_menu_pause::EXIT:
				_sprites["Quit_Current"] = _sprites["Quit"];
				_sprites["Options_Current"] = _sprites["Options_On"];
				_offset = e_menu_pause::SETTINGS_PAUSE;
				break;
			}
		}
		else if (Keyboard::isDown(Keyboard::Down))
		{
			Game::getInstance().getSoundSystem()->playSound("Menu", false);
			switch (_offset)
			{
			case e_menu_pause::RESUME:
				_sprites["Resume_Current"] = _sprites["Resume"];
				_sprites["HowToPlay_Current"] = _sprites["HowToPlay_On"];
				_offset = e_menu_pause::HOW_TO_PLAY_PAUSE;
				break;
			case e_menu_pause::HOW_TO_PLAY_PAUSE:
				_sprites["HowToPlay_Current"] = _sprites["HowToPlay"];
				_sprites["Options_Current"] = _sprites["Options_On"];
				_offset = e_menu_pause::SETTINGS_PAUSE;
				break;
			case e_menu_pause::SETTINGS_PAUSE:
				_sprites["Options_Current"] = _sprites["Options"];
				_sprites["Quit_Current"] = _sprites["Quit_On"];
				_offset = e_menu_pause::EXIT;
				break;
			case e_menu_pause::EXIT:
				_sprites["Quit_Current"] = _sprites["Quit"];
				_sprites["Resume_Current"] = _sprites["Resume_On"];
				_offset = e_menu_pause::RESUME;
				break;
			}
		}

		_window->clear();
		_window->draw(_sprites["Background"].get());
		_window->draw(_sprites["Pause"].get());
		_window->draw(_sprites["Resume_Current"].get());
		_window->draw(_sprites["HowToPlay_Current"].get());
		_window->draw(_sprites["Options_Current"].get());
		_window->draw(_sprites["Quit_Current"].get());
		_window->display();

		return true;
	}

	void	MenuPause::clean()
	{

	}
}