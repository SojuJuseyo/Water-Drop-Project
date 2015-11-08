#pragma once

#include "Window.h"
#include "Keyboard.h"
#include "d3d.h"
#include "Fps.h"
#include "Vector2f.h"
#include "Character.h"
#include "Sprite.h"

#include <vector>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Moo::Window window(hInstance, Moo::WindowSettings("Water Drop"));

	Moo::Sprite *mario = new Moo::Sprite(60, 60, 60, 100);
	mario->loadTexture("mario.dds");
	Moo::Sprite *platform = new Moo::Sprite(300, 40, 150, 150);
	platform->loadTexture("platform.dds");
	Moo::Sprite *background = new Moo::Sprite(WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0);
	background->loadTexture("background.dds");
	Moo::Sprite *ground = new Moo::Sprite(40, 40, 0, 0);
	ground->loadTexture("ground.dds");
	Moo::Character	*player = new Moo::Character(Moo::Vector2f(1, 0), 50, mario, true);

	std::vector<std::pair<std::string, Moo::Character *>> entities;

	entities.push_back(std::make_pair("Player 1", new Moo::Character(Moo::Vector2f(1, 0), 50, mario, true)));
	entities.push_back(std::make_pair("Platform", new Moo::Character(Moo::Vector2f(1, 0), 0, platform, false)));

	for (float i = 0; i < 20; ++i) {
		Moo::Sprite *tmpGround = new Moo::Sprite(40, 40, i * 40, 0);
		tmpGround->loadTexture("ground.dds");
		entities.push_back(std::make_pair("Bottom", new Moo::Character(Moo::Vector2f(1, 0), 0, tmpGround, false)));
	}
	//entities.push_back(std::make_pair("Background", new Moo::Character(Moo::Vector2f(1, 0), 0, background, false)));

	HitZone tmp = HitZone::NONE;

	window.setFpsLimit(FPS_LIMIT);

	FILE * pConsole;
	AllocConsole();
	freopen_s(&pConsole, "CONOUT$", "wb", stdout);

	float save_x, save_y;
	while (window.isOpen())
	{
		save_x = entities[0].second->getSprite()->getX();
		save_y = entities[0].second->getSprite()->getY();
		if (Moo::Keyboard::isPressed(Moo::Keyboard::Left))
			entities[0].second->move(Direction::LEFT);
		else if (Moo::Keyboard::isPressed(Moo::Keyboard::Right))
			entities[0].second->move(Direction::RIGHT);
		else if (Moo::Keyboard::isPressed(Moo::Keyboard::Space))
		{
			entities[0].second->jump();
			entities[0].second->setGravity(true);
			entities[0].second->getSprite()->rotate(50);
		}

		for (unsigned int i = 0; i < entities.size(); ++i)
			if (entities[i].second->getGravity() == true)
				entities[i].second->update();

		for (unsigned int i = 1; i < entities.size(); ++i)
		{
			if ((tmp = entities[0].second->collisionAABB(entities[i].second)) != HitZone::NONE)
			{
				//std::cout << "COLLIDING with " << entities[i].first << " : ";
				if (tmp == HitZone::BOTTOM || tmp == HitZone::TOP)
				{
					if (tmp == HitZone::BOTTOM)
					{
						entities[0].second->resetPos();
						entities[0].second->setGravity(false);
						//std::cout << "BOTTOM";
					}
					else
					{
						entities[0].second->getSprite()->setX(save_x);
						//std::cout << "TOP";
					}
					entities[0].second->getSprite()->setY(save_y);
				}
				else
				{
					//if (tmp == HitZone::RIGHT_SIDE) std::cout << "RIGHT_SIDE";
					//else std::cout << "LEFT_SIDE";
					entities[0].second->getSprite()->setX(save_x);
					//std::cout << std::endl;
				}
				/*std::cout << "nextX : " << entities[0].second->getSprite()->getX()
					<< " && X : " << save_x
					<< "nextY : " << entities[0].second->getSprite()->getY()
					<< " && Y : " << save_y << std::endl;*/
			}
			else
				entities[0].second->setGravity(true);
		}

		window.clear();
		for (unsigned int i = 0; i < entities.size(); ++i) {
			window.draw(entities[i].second->getSprite());
		}
		window.draw(player->getHitboxSprite());
		window.display();
	}
	mario->release();
	window.destroy();
	return 0;
}
