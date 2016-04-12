#include "Menu.h"

namespace Moo
{
	Menu::Menu()
	{
	}


	Menu::~Menu()
	{
	}

	bool Menu::init(SoundSystem *soundSystem)
	{
		//background
		backgroundText = new Texture;
		backgroundText->loadFromFile("Menu_WTP_DDS.dds");
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

		//init sound system
		this->soundSystem = soundSystem;

		_offset = e_menu::PLAY;
		return true;
	}


	bool Menu::run(Moo::Window &window)
	{
		while (window.isOpen())
		{
			if (Moo::Keyboard::isDown(Keyboard::Enter))
				switch (_offset)
				{
				case e_menu::PLAY:
					Game::getInstance().runScene(TypeScene::LEVEL, TypeScene::MENU, window);
					return true;
					break;
				case e_menu::CONTROLS:
					Game::getInstance().runScene(TypeScene::CONTROLE, TypeScene::MENU, window);
					return true;
					break;
				case e_menu::QUIT:
					Game::getInstance().setExit(true);
					return (false);
					break;
				}

			if (Keyboard::isDown(Keyboard::Up)) {
				soundSystem->playSound("menu", false);
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
				soundSystem->playSound("menu", false);
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

		//backgroundText->release();
		return false;
	}

	void	Menu::clean()
	{

	}
}