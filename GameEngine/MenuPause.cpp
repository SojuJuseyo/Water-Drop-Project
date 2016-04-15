#include "MenuPause.h"

namespace Moo
{
	MenuPause::MenuPause()
	{
	}


	MenuPause::~MenuPause()
	{
	}

	bool MenuPause::init()
	{

		//background
		backgroundText = new Texture;
		backgroundText->loadFromFile("Menu_Pause_WTP_DDS.dds");
		background = new Sprite(d3d::getInstance().getScreenSize().x, d3d::getInstance().getScreenSize().y, 0, 0);
		background->loadTexture(backgroundText);

		//Buttons attributes
		float spaceBetweenButtons = 10;
		float positionOfButtonsX = d3d::getInstance().getScreenSize().x / 5.f * 2.5f;
		float widthOfButtons = 200;
		float heightOfButtons = 75;

		//Buttons
		buttonText = new Texture;
		buttonText->loadFromFile("hitbox.dds");

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

		//init sound system
		this->soundSystem = Game::getInstance().getSoundSystem();

		_offset = e_menu_pause::RESUME;
		return true;
	}

	bool MenuPause::run(Moo::Window &window)
	{
		while (window.isOpen())
		{
			if (Moo::Keyboard::isDown(Keyboard::Enter))
				switch (_offset)
				{
				case e_menu_pause::RESUME:
					Game::getInstance().runScene(TypeScene::LEVEL, TypeScene::PAUSE, window);
					return true;
					break;
				case e_menu_pause::HOW_TO_PLAY:
					Game::getInstance().runScene(TypeScene::CONTROLE, TypeScene::PAUSE, window);
					return true;
					break;
				case e_menu_pause::EXIT:
					Game::getInstance().setExit(true);
					return (false);
					break;
				}

			if (Keyboard::isDown(Keyboard::Up)) {
				soundSystem->playSound("menu", false);
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
				soundSystem->playSound("menu", false);
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

			window.clear();
			window.draw(background);

			switch (_offset)
			{
			case e_menu_pause::RESUME:
				window.draw(button_resume);
				break;
			case e_menu_pause::HOW_TO_PLAY:
				window.draw(button_controls);
				break;
			case e_menu_pause::EXIT:
				window.draw(button_quit);
				break;
			}
			window.display();
		}

		//backgroundText->release();
		return false;
	}

	void	MenuPause::clean()
	{

	}
}