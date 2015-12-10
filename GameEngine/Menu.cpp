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

		//buttons
		Texture *buttonText = new Texture;
		buttonText->loadFromFile("hitbox.dds");
		Sprite *button_play = new Sprite(100, 100, WINDOW_WIDTH / 5 * 3, WINDOW_HEIGHT / 4 * 3);
		button_play->loadTexture(buttonText);
		Sprite *button_controls = new Sprite(100, 100, WINDOW_WIDTH / 5 * 3, WINDOW_HEIGHT / 4 * 2);
		button_controls->loadTexture(buttonText);
		Sprite *button_quit = new Sprite(100, 100, WINDOW_WIDTH / 5 * 3, WINDOW_HEIGHT / 4);
		button_quit->loadTexture(buttonText);

		_offset = e_menu::PLAY;

		Scene *newscene;
		while (window.isOpen())
		{
			if (Moo::Keyboard::isPressed(Keyboard::Enter))
				switch (_offset)
				{
					case e_menu::PLAY:
						newscene = new LevelScene;
						Game::getInstance().setScene(newscene);
						return (true);
						break;
					case e_menu::CONTROLS:
						return (false);
						break;
					case e_menu::QUIT:
						return (false);
						break;
				}

			if (Keyboard::isPressed(Keyboard::Up))
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
			else if (Keyboard::isPressed(Keyboard::Down))
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