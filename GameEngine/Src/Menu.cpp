#include "../Includes/Menu.h"

namespace Moo
{
	Menu::Menu()
	{
	}

	Menu::~Menu()
	{
	}

	bool Menu::init(std::shared_ptr<Moo::Window> window)
	{
		_window = window;

		//background
		backgroundText = new Texture;
		backgroundText->loadFromFile(GRAPHICS_PATH + std::string("Menu_WTP_DDS.dds"));
		background = new Sprite(d3d::getInstance().getScreenSize().x, d3d::getInstance().getScreenSize().y, 0, 0);
		background->loadTexture(backgroundText);

		//Buttons attributes
		float spaceBetweenButtons = 10;
		float positionOfButtonsX = d3d::getInstance().getScreenSize().x / 5.f * 2.5f;
		float widthOfButtons = 200;
		float heightOfButtons = 75;

		//Buttons
		buttonText = new Texture;
		buttonText->loadFromFile(GRAPHICS_PATH + std::string("hitbox.dds"));

		//Button Play
		button_play = new Sprite(widthOfButtons,
			heightOfButtons,
			positionOfButtonsX,
			d3d::getInstance().getScreenSize().y / 10 * 6);
		button_play->loadTexture(buttonText);

		//Button Controls
		button_controls = new Sprite(widthOfButtons,
			heightOfButtons,
			positionOfButtonsX,
			button_play->getY() - heightOfButtons - spaceBetweenButtons); //Place it below the Play button
		button_controls->loadTexture(buttonText);

		//Button Quit
		button_quit = new Sprite(widthOfButtons,
			heightOfButtons,
			positionOfButtonsX,
			button_controls->getY() - heightOfButtons - spaceBetweenButtons); //Place it below the Controls button
		button_quit->loadTexture(buttonText);

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
				Game::getInstance().runScene(Game::LEVEL1);
				return true;
				break;
			case e_menu::CONTROLS:
				Game::getInstance().runScene(Game::CONTROLS_MENU);
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
		_window->draw(background);

		switch (_offset)
		{
		case e_menu::PLAY:
			_window->draw(button_play);
			break;
		case e_menu::CONTROLS:
			_window->draw(button_controls);
			break;
		case e_menu::QUIT:
			_window->draw(button_quit);
			break;
		}
		_window->display();
		return true;
	}

	void	Menu::clean()
	{

	}
}