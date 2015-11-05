#pragma once

#include "Window.h"
#include "Keyboard.h"
#include "d3d.h"
#include "Fps.h"
#include "Vector2f.h"
#include "Character.h"
#include <vector>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Moo::Window window(hInstance, Moo::WindowSettings("test"));
	Moo::RectangleShape *p1 = new Moo::RectangleShape(50, 50, 200, WINDOW_HEIGHT - 101, DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
	Moo::RectangleShape *p2 = new Moo::RectangleShape(50, 50, 300, WINDOW_HEIGHT - 101, DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f));
	Moo::RectangleShape *platform = new Moo::RectangleShape(300, 50, 200, WINDOW_HEIGHT - 300, DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f));
	Moo::RectangleShape *bottom = new Moo::RectangleShape(WINDOW_WIDTH, 50, 0, WINDOW_HEIGHT - 50, DirectX::XMFLOAT4(0, 0, 0, 0));
	std::vector<std::pair<std::string, Moo::Character *>> entities;
	
	entities.push_back(std::make_pair("Player 1", new Moo::Character(Moo::Vector2f(1, 0), 50, p1, true)));
	entities.push_back(std::make_pair("Player 2", new Moo::Character(Moo::Vector2f(1, 0), 50, p2, false)));
	entities.push_back(std::make_pair("Platform", new Moo::Character(Moo::Vector2f(1, 0), 0, platform, false)));
	entities.push_back(std::make_pair("Bottom", new Moo::Character(Moo::Vector2f(1, 0), 0, bottom, false)));

	HitZone tmp = HitZone::NONE;

	window.setFpsLimit(FPS_LIMIT);
	FILE * pConsole;; AllocConsole();
	freopen_s(&pConsole, "CONOUT$", "wb", stdout);
	float save_x, save_y;
	while (window.isOpen())
	{
		save_x = entities[0].second->getSprite()->getX();
		save_y = entities[0].second->getSprite()->getY();
		//std::cout << "FPS: " << window.getFps() << std::endl;
		if (Moo::Keyboard::isPressed(Moo::Keyboard::Left))
			entities[0].second->move(Direction::LEFT);
		else if (Moo::Keyboard::isPressed(Moo::Keyboard::Right))
			entities[0].second->move(Direction::RIGHT);
		else if (Moo::Keyboard::isPressed(Moo::Keyboard::Space))
		{
			entities[0].second->jump();
			entities[0].second->setGravity(true);
		}
		
		for (unsigned int i = 0; i < entities.size(); ++i)
			if (entities[i].second->getGravity() == true)
				entities[i].second->update();
		
		for (unsigned int i = 1; i < entities.size(); ++i)
		{
			if ((tmp = entities[0].second->collisionAABB(entities[i].second)) != HitZone::NONE)
			{
				std::cout << "COLLIDING with " << entities[i].first << " : ";
				if (tmp == HitZone::BOTTOM || tmp == HitZone::TOP)
				{
					if (tmp == HitZone::BOTTOM)
					{
						entities[0].second->resetPos();
						entities[0].second->setGravity(false);
						std::cout << "BOTTOM";
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
					std::cout << std::endl;
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
		for (unsigned int i = 0; i < entities.size(); ++i)
			window.draw(entities[i].second->getSprite());
		window.display();
	}
	window.destroy();
	return 0;
}
