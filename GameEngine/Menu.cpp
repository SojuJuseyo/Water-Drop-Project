#include "Menu.h"

namespace Moo
{
	Menu::Menu()
	{
	}


	Menu::~Menu()
	{
	}

	bool Menu::run(Moo::Window &window)
	{
		//background
		Texture *backgroundText = new Texture;
		backgroundText->loadFromFile("menu_WTP.dds");
		Sprite *background = new Sprite(WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0);
		background->loadTexture(backgroundText);

		//Buttons attributes
		unsigned int spaceBetweenButtons = 10;
		unsigned int positionOfButtonsX = WINDOW_WIDTH / 5 * 2.5;
		unsigned int widthOfButtons = 200;
		unsigned int heightOfButtons = 75;

		//Buttons
		Texture *buttonText = new Texture;
		buttonText->loadFromFile("hitbox.dds");

		//Button Play
		Sprite *button_play = new Sprite(widthOfButtons,
										 heightOfButtons,
										 positionOfButtonsX,
										 WINDOW_HEIGHT / 10 * 6);
		button_play->loadTexture(buttonText);

		//Button Controls
		Sprite *button_controls = new Sprite(widthOfButtons,
											 heightOfButtons,
											 positionOfButtonsX,
											 button_play->getY() - heightOfButtons - spaceBetweenButtons); //Place it below the Play button
		button_controls->loadTexture(buttonText);

		//Button Quit
		Sprite *button_quit = new Sprite(widthOfButtons,
										 heightOfButtons,
										 positionOfButtonsX,
										 button_controls->getY() - heightOfButtons - spaceBetweenButtons); //Place it below the Controls button
		button_quit->loadTexture(buttonText);

		_offset = e_menu::PLAY;

		Scene *newscene;
		while (window.isOpen())
		{
			if (Moo::Keyboard::isDown(Keyboard::Enter))
				switch (_offset)
				{
					case e_menu::PLAY:
						newscene = new LevelScene;
						Game::getInstance().runScene(newscene, window);
						return true;
						break;
					case e_menu::CONTROLS:
						return (false);
						break;
					case e_menu::QUIT:
						return (false);
						break;
				}

			if (Keyboard::isDown(Keyboard::Up))
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
			else if (Keyboard::isDown(Keyboard::Down))
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

			window.clear();
			window.draw(background);

			switch (_offset)
			{
				case e_menu::PLAY:
					window.draw(button_play);
					break;
				case e_menu::CONTROLS:
					window.draw(button_controls);
					break;
				case e_menu::QUIT:
					window.draw(button_quit);
					break;
			}
			window.display();
		}

		backgroundText->release();
		return false;
	}

	void	Menu::clean()
	{

	}
}