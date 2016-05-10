#include "MenuPause.h"

namespace Moo
{
	MenuPause::MenuPause()
	{
	}


	MenuPause::~MenuPause()
	{
	}

	bool MenuPause::init(std::shared_ptr<Moo::Window> window, std::map<std::string, Texture> textures)
	{
		_window = window;
		_textures = std::make_shared<std::map<std::string, Texture>>(textures);

		//background
		_sprites["Background"] = std::make_shared<Sprite>(d3d::getInstance().getScreenSize().x, d3d::getInstance().getScreenSize().y, 0.f, 0.f);
		_sprites["Background"]->loadTexture(&_textures.get()->at("Background_Menu_Pause"));

		//Buttons attributes
		float spaceBetweenButtons = 10;
		float positionOfButtonsX = d3d::getInstance().getScreenSize().x / 5.f * 2.5f;
		float widthOfButtons = 200;
		float heightOfButtons = 75;

		//Button Play
		_sprites["Resume"] = std::make_shared<Sprite>(widthOfButtons,
			heightOfButtons,
			positionOfButtonsX,
			d3d::getInstance().getScreenSize().y / 10 * 6);
		_sprites["Resume"]->loadTexture(&_textures.get()->at("Hitbox"));

		//Button Controls
		_sprites["Controls"] = std::make_shared<Sprite>(widthOfButtons,
			heightOfButtons,
			positionOfButtonsX,
			_sprites["Resume"]->getY() - heightOfButtons - spaceBetweenButtons); //Place it below the Play button
		_sprites["Controls"]->loadTexture(&_textures.get()->at("Hitbox"));

		//Button Quit
		_sprites["Quit"] = std::make_shared<Sprite>(widthOfButtons,
			heightOfButtons,
			positionOfButtonsX,
			_sprites["Controls"]->getY() - heightOfButtons - spaceBetweenButtons); //Place it below the Controls button
		_sprites["Quit"]->loadTexture(&_textures.get()->at("Hitbox"));

		_offset = e_menu_pause::RESUME;
		return true;
	}

	bool MenuPause::runUpdate()
	{
		Moo::Keyboard::updateInput();

		if (Moo::Keyboard::isDown(Keyboard::Enter))
			switch (_offset)
			{
			case e_menu_pause::RESUME:
				Game::getInstance().backToPrevScene();
				return true;
				break;
			case e_menu_pause::HOW_TO_PLAY:
				Game::getInstance().runScene(Game::CONTROLS_MENU, false);
				return true;
				break;
			case e_menu_pause::EXIT:
				Game::getInstance().runScene(Game::MAIN_MENU, false);
				return true;
				break;
			}

		if (Keyboard::isDown(Keyboard::Up)) {
			Game::getInstance().getSoundSystem()->playSound("Menu", false);
			switch (_offset)
			{
			case e_menu_pause::RESUME:
				_offset = e_menu_pause::EXIT;
				break;
			case e_menu_pause::HOW_TO_PLAY:
				_offset = e_menu_pause::RESUME;
				break;
			case e_menu_pause::EXIT:
				_offset = e_menu_pause::HOW_TO_PLAY;
				break;
			}
		}
		else if (Keyboard::isDown(Keyboard::Down)) {
			Game::getInstance().getSoundSystem()->playSound("Menu", false);
			switch (_offset)
			{
			case e_menu_pause::RESUME:
				_offset = e_menu_pause::HOW_TO_PLAY;
				break;
			case e_menu_pause::HOW_TO_PLAY:
				_offset = e_menu_pause::EXIT;
				break;
			case e_menu_pause::EXIT:
				_offset = e_menu_pause::RESUME;
				break;
			}
		}

		_window->clear();
		_window->draw(_sprites["Background"].get());

		switch (_offset)
		{
		case e_menu_pause::RESUME:
			_window->draw(_sprites["Resume"].get());
			break;
		case e_menu_pause::HOW_TO_PLAY:
			_window->draw(_sprites["Controls"].get());
			break;
		case e_menu_pause::EXIT:
			_window->draw(_sprites["Quit"].get());
			break;
		}
		_window->display();

		return true;
	}

	void	MenuPause::clean()
	{

	}
}