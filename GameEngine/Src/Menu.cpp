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
		_sprites["Background"] = std::make_shared<Moo::Sprite>(1280.f, 1080.f, 0.f, 0.f);
		_sprites["Background"]->setScale(Vector2f(0.65f, 0.56f));
		_sprites["Background"]->loadTexture(&_textures.get()->at("Background_Menu"));

		//Buttons attributes
		float spaceBetweenButtons = 10;
		float positionOfButtonsX = d3d::getInstance().getScreenSize().x / 5.f * 2.5f;
		float widthOfButtons = 200;
		float heightOfButtons = 75;

		//Button Play
		_sprites["Play"] = std::make_shared<Sprite>(widthOfButtons,
			heightOfButtons,
			positionOfButtonsX,
			d3d::getInstance().getScreenSize().y / 10 * 6);
		_sprites["Play"]->loadTexture(&_textures.get()->at("Hitbox"));

		//Button Controls
		_sprites["Controls"] = std::make_shared<Sprite>(widthOfButtons,
			heightOfButtons,
			positionOfButtonsX,
			_sprites["Play"]->getY() - heightOfButtons - spaceBetweenButtons); //Place it below the Play button
		_sprites["Controls"]->loadTexture(&_textures.get()->at("Hitbox"));

		//Button Quit
		_sprites["Quit"] = std::make_shared<Sprite>(widthOfButtons,
			heightOfButtons,
			positionOfButtonsX,
			_sprites["Controls"]->getY() - heightOfButtons - spaceBetweenButtons); //Place it below the Controls button
		_sprites["Quit"]->loadTexture(&_textures.get()->at("Hitbox"));

		_offset = e_menu::PLAY;
		return true;
	}


	bool Menu::runUpdate()
	{
		Moo::Keyboard::updateInput();

		if (Moo::Keyboard::isDown(Keyboard::Enter))
			switch (_offset)
			{
			case e_menu::PLAY:
				Game::getInstance().runScene(Game::LEVEL1, false);
				return true;
				break;
			case e_menu::CONTROLS:
				Game::getInstance().runScene(Game::CONTROLS_MENU, false);
				return true;
				break;
			case e_menu::QUIT:
				return false;
				break;
			}

		if (Keyboard::isDown(Keyboard::Up)) {
			Game::getInstance().getSoundSystem()->playSound("Menu", false);
			switch (_offset)
			{
			case e_menu::PLAY:
				_offset = e_menu::QUIT;
				break;
			case e_menu::CONTROLS:
				_offset = e_menu::PLAY;
				break;
			case e_menu::QUIT:
				_offset = e_menu::CONTROLS;
				break;
			}
		}
		else if (Keyboard::isDown(Keyboard::Down)) {
			Game::getInstance().getSoundSystem()->playSound("Menu", false);
			switch (_offset)
			{
			case e_menu::PLAY:
				_offset = e_menu::CONTROLS;
				break;
			case e_menu::CONTROLS:
				_offset = e_menu::QUIT;
				break;
			case e_menu::QUIT:
				_offset = e_menu::PLAY;
				break;
			}
		}

		_window->clear();
		_window->draw(_sprites["Background"].get());

		switch (_offset)
		{
		case e_menu::PLAY:
			_window->draw(_sprites["Play"].get());
			break;
		case e_menu::CONTROLS:
			_window->draw(_sprites["Controls"].get());
			break;
		case e_menu::QUIT:
			_window->draw(_sprites["Quit"].get());
			break;
		}
		_window->display();
		return true;
	}

	void	Menu::clean()
	{

	}
}