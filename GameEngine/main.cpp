#pragma once

#include "Window.h"
#include "Keyboard.h"
#include "d3d.h"
#include "Fps.h"
#include "Vector2f.h"
#include "Character.h"
#include "Sprite.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Moo::Window window(hInstance, Moo::WindowSettings("test"));
	Moo::RectangleShape *rectangle = new Moo::RectangleShape(50, 50, 200, WINDOW_HEIGHT - 50, DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
	Moo::Character	*player = new Moo::Character(Moo::Vector2f(1, 0), 50, rectangle);
	Moo::Sprite *sprite = new Moo::Sprite(50, 50, 200, WINDOW_HEIGHT - 50);
	window.setFpsLimit(FPS_LIMIT);
	FILE * pConsole;; AllocConsole();
	freopen_s(&pConsole, "CONOUT$", "wb", stdout);
	sprite->loadTexture();
	while (window.isOpen())
	{
		//std::cout << "FPS: " << window.getFps() << std::endl;
		if (Moo::Keyboard::isPressed(Moo::Keyboard::Left)) {
			player->move(Direction::LEFT);
		}
		else if (Moo::Keyboard::isPressed(Moo::Keyboard::Right)) {
			player->move(Direction::RIGHT);
		}
		else if (Moo::Keyboard::isPressed(Moo::Keyboard::Space)) {
			player->jump();
		}
		player->update();
		window.clear();
		window.draw(rectangle);
		window.draw(sprite);
		window.display();
	}
	sprite->release();
	window.destroy();
	return 0;
}
