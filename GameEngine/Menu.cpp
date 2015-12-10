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
		Sprite *button_play = new Sprite(200, 200, WINDOW_WIDTH / 5 * 3, WINDOW_HEIGHT / 4 * 3);
		Sprite *button_controls = new Sprite(200, 200, WINDOW_WIDTH / 5 * 3, WINDOW_HEIGHT / 4 * 2);
		Sprite *button_quit = new Sprite(200, 200, WINDOW_WIDTH / 5 * 3, WINDOW_HEIGHT / 4);

		_offset = e_menu::PLAY;

		auto newscene = new LevelScene;

		while (window.isOpen())
		{
			if (Moo::Keyboard::isPressed(Keyboard::Enter))
				switch (_offset)
				{
					case e_menu::PLAY:
						Game::getInstance().setScene(newscene);
						return (false);
					case e_menu::CONTROLS:
						return (false);
					case e_menu::QUIT:
						return false;
				}

			if (Keyboard::isPressed(Keyboard::Up))
				switch (_offset)
				{
					case e_menu::PLAY:
						_offset = e_menu::QUIT;
					case e_menu::CONTROLS:
						_offset = e_menu::PLAY;
					case e_menu::QUIT:
						_offset = e_menu::CONTROLS;
				}
			else if (Keyboard::isPressed(Keyboard::Down))
				switch (_offset)
				{
					case e_menu::PLAY:
						_offset = e_menu::CONTROLS;
					case e_menu::CONTROLS:
						_offset = e_menu::QUIT;
					case e_menu::QUIT:
						_offset = e_menu::PLAY;
				}

			window.clear();
			window.draw(background);

			switch (_offset)
			{
				case e_menu::PLAY:
					window.draw(button_play);
				case e_menu::CONTROLS:
					window.draw(button_controls);
				case e_menu::QUIT:
					window.draw(button_quit);
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