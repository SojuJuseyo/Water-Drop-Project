#include "../Includes/MenuPause.h"

namespace Moo
{
	MenuPause::MenuPause()
	{
	}


	MenuPause::~MenuPause()
	{
	}

	bool MenuPause::init(std::shared_ptr<Moo::Window> window)
	{
		_window = window;

		//background
		backgroundText = new Texture;
		backgroundText->loadFromFile(GRAPHICS_PATH + std::string("Menu_Pause_WTP_DDS.dds"));
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

		//Button Resume
		button_resume = new Sprite(widthOfButtons,
			heightOfButtons,
			positionOfButtonsX,
			d3d::getInstance().getScreenSize().y / 10 * 6);
		button_resume->loadTexture(buttonText);

		//Button Controls
		button_controls = new Sprite(widthOfButtons,
			heightOfButtons,
			positionOfButtonsX,
			button_resume->getY() - heightOfButtons - spaceBetweenButtons); //Place it below the Resume button
		button_controls->loadTexture(buttonText);

		//Button Quit
		button_quit = new Sprite(widthOfButtons,
			heightOfButtons,
			positionOfButtonsX,
			button_controls->getY() - heightOfButtons - spaceBetweenButtons); //Place it below the Controls button
		button_quit->loadTexture(buttonText);

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
				Game::getInstance().runScene(Game::LEVEL1);
				return true;
				break;
			case e_menu_pause::HOW_TO_PLAY:
				Game::getInstance().runScene(Game::CONTROLS_MENU);
				return true;
				break;
			case e_menu_pause::EXIT:
				Game::getInstance().runScene(Game::MAIN_MENU);
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
		_window->draw(background);

		switch (_offset)
		{
		case e_menu_pause::RESUME:
			_window->draw(button_resume);
			break;
		case e_menu_pause::HOW_TO_PLAY:
			_window->draw(button_controls);
			break;
		case e_menu_pause::EXIT:
			_window->draw(button_quit);
			break;
		}
		_window->display();

		return true;
	}

	void	MenuPause::clean()
	{

	}
}