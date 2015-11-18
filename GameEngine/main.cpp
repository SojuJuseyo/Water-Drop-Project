#pragma once

#include "Window.h"
#include "Keyboard.h"
#include "d3d.h"
#include "Fps.h"
#include "Vector2f.h"
#include "Character.h"
#include "Sprite.h"
#include "Text.h"

#include <vector>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Moo::Window window(hInstance, Moo::WindowSettings("Water Drop"));
	
	Moo::Text *text = new Moo::Text("test", 20, 20, 20, 0);

	Moo::Sprite *mario = new Moo::Sprite(60, 60, 0, WINDOW_HEIGHT);
	mario->loadTexture("mario.dds");
	Moo::Sprite *enemySprite = new Moo::Sprite(60, 60, 250, 200);
	enemySprite->loadTexture("mario.dds");
	Moo::Sprite *platform = new Moo::Sprite(300, 40, 150, 150);
	platform->loadTexture("platform.dds");
	Moo::Sprite *platform2 = new Moo::Sprite(300, 40, 450, 250);
	platform2->loadTexture("platform.dds");
	Moo::Sprite *background = new Moo::Sprite(WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0);
	background->loadTexture("background.dds");
	Moo::Sprite *ground = new Moo::Sprite(40, 40, 0, 0);
	ground->loadTexture("ground.dds");
	Moo::Character *player = new Moo::Character(Moo::Vector2f(3, 0), 300, mario, true);
	Moo::Character *platformEntity = new Moo::Character(Moo::Vector2f(1, 0), 0, platform, false);
	Moo::Character *platformEntity2 = new Moo::Character(Moo::Vector2f(1, 0), 0, platform2, false);

	std::vector<std::pair<std::string, Moo::Character *>> entities;
	Moo::Character *enemy = new Moo::Character(Moo::Vector2f(1, 0), 0, enemySprite, false);
	enemy->setCollision(true);
	entities.push_back(std::make_pair("Player 1", player));
	entities.push_back(std::make_pair("Platform 1", platformEntity));
	entities.push_back(std::make_pair("Platform 2", platformEntity2));
	entities.push_back(std::make_pair("Enemy", enemy));

	for (float i = 0; i < 20; ++i) {
		Moo::Sprite *tmpGround = new Moo::Sprite(40, 40, i * 40, 0);
		tmpGround->loadTexture("ground.dds");
		entities.push_back(std::make_pair("Bottom", new Moo::Character(Moo::Vector2f(1, 0), 0, tmpGround, false)));
	}

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

		if (Moo::Keyboard::isPressed(Moo::Keyboard::Left)) {
			entities[0].second->move(Direction::LEFT);
		}
		else if (Moo::Keyboard::isPressed(Moo::Keyboard::Right)) {
			entities[0].second->move(Direction::RIGHT);
		}
		else if (Moo::Keyboard::isPressed(Moo::Keyboard::Space))
		{
			entities[0].second->jump();
			entities[0].second->setGravity(true);
		}
		else if (Moo::Keyboard::isPressed(Moo::Keyboard::Up))
		{
			Moo::d3d::getInstance().getCamera()->move(Moo::Vector2f(10, 0));
		}

		for (unsigned int i = 0; i < entities.size(); ++i)
			if (entities[i].second->getGravity() == true)
				entities[i].second->update();

		for (unsigned int i = 1; i < entities.size(); ++i)
		{
			if ((tmp = entities[0].second->collisionAABB(entities[i].second)) != HitZone::NONE 
				&& entities[i].second->isCollidable())
			{
				//std::cout << "COLLIDING with " << entities[i].first << " : ";
				if (tmp == HitZone::BOTTOM || tmp == HitZone::TOP)
				{
					entities[0].second->resetPos();
					if (tmp == HitZone::BOTTOM)
					{
						//Moo::Hitbox A = entities[0].second->getHitbox();
						//Moo::Hitbox B = entities[i].second->getHitbox();
						//std::cout << "Hitbox A : x1 " << A.x1 << " y1 " << A.y1 << " x2 " << A.x2 << " y2 " << A.y2 << std::endl;
						//std::cout << "Hitbox B : x1 " << B.x1 << " y1 " << B.y1 << " x2 " << B.x2 << " y2 " << B.y2 << std::endl;
						//std::cout << "Character : X " << save_x << " Y " << save_y << std::endl;
						entities[0].second->setGravity(false);
						//std::cout << "BOTTOM";
					}
					else
					{
						entities[0].second->getSprite()->setX(save_x);
						std::cout << "TOP";
					}
					entities[0].second->getSprite()->setY(save_y);
				}
				else
				{
					if (tmp == HitZone::RIGHT_SIDE) std::cout << "RIGHT_SIDE";
					else std::cout << "LEFT_SIDE";
					entities[0].second->getSprite()->setX(save_x);
				}
				std::cout << std::endl;
				if (entities[i].first == "Enemy")
				{
					entities[0].second->getSprite()->scale(Moo::Vector2f(0.5, 0.5));
					entities[0].second->getHitboxSprite()->setScale(entities[0].second->getSprite()->getScale());
					entities[0].second->resetHitbox();
					entities.erase(entities.begin() + i);
				}
			}
			else
				entities[0].second->setGravity(true);
		}

		window.clear();
		window.draw(background);
		enemy->getSprite()->rotate(1);
		for (unsigned int i = 0; i < entities.size(); ++i) {
			window.draw(entities[i].second->getSprite());
		}
		window.draw(player->getHitboxSprite());
		window.draw(platformEntity->getHitboxSprite());
		text->setText(std::to_string(window.getFps()));
		window.draw(text);
		window.display();
	}
	mario->release();
	window.destroy();
	return 0;
}
