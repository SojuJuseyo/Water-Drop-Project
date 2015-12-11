#include "MenuPause.h"

namespace Moo
{
	MenuPause::MenuPause()
	{
	}


	MenuPause::~MenuPause()
	{
	}

	bool MenuPause::run(Moo::Window &window)
	{
		//background
		Texture *backgroundText = new Texture;
		backgroundText->loadFromFile("Menu_Pause_WTP_DDS.dds");
		Sprite *background = new Sprite(WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0);
		background->loadTexture(backgroundText);

		//Buttons attributes
		float spaceBetweenButtons = 10;
		float positionOfButtonsX = WINDOW_WIDTH / 5 * 2.5;
		float widthOfButtons = 200;
		float heightOfButtons = 75;

		//Buttons
		Texture *buttonText = new Texture;
		buttonText->loadFromFile("hitbox.dds");

		//Button Resume
		Sprite *button_resume = new Sprite(widthOfButtons,
			heightOfButtons,
			positionOfButtonsX,
			WINDOW_HEIGHT / 10 * 6);
		button_resume->loadTexture(buttonText);

		//Button Controls
		Sprite *button_controls = new Sprite(widthOfButtons,
			heightOfButtons,
			positionOfButtonsX,
			button_resume->getY() - heightOfButtons - spaceBetweenButtons); //Place it below the Resume button
		button_controls->loadTexture(buttonText);

		//Button Quit
		Sprite *button_quit = new Sprite(widthOfButtons,
			heightOfButtons,
			positionOfButtonsX,
			button_controls->getY() - heightOfButtons - spaceBetweenButtons); //Place it below the Controls button
		button_quit->loadTexture(buttonText);

		_offset = e_menu_pause::RESUME;

		Scene *newscene;
		while (window.isOpen())
		{
			if (Moo::Keyboard::isDown(Keyboard::Enter))
				switch (_offset)
				{
				case e_menu_pause::RESUME:
					newscene = new LevelScene;
					Game::getInstance().runScene(newscene, window);
					return true;
					break;
				case e_menu_pause::HOW_TO_PLAY:
					return (false);
					break;
				case e_menu_pause::EXIT:
					return (false);
					break;
				}

			if (Keyboard::isDown(Keyboard::Up))
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
			else if (Keyboard::isDown(Keyboard::Down))
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

		backgroundText->release();
		return false;
	}

	void	MenuPause::clean()
	{

	}
}