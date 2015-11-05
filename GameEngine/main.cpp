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
	Moo::RectangleShape *rectangle = new Moo::RectangleShape(50, 50, 200, WINDOW_HEIGHT - 250, DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
	Moo::Sprite *mario = new Moo::Sprite(60, 60, 60, 40);
	mario->loadTexture("mario.dds");
	Moo::Character	*player = new Moo::Character(Moo::Vector2f(1, 0), 50, mario);
	Moo::Sprite *background = new Moo::Sprite(WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0);

	window.setFpsLimit(FPS_LIMIT);
	FILE * pConsole;; AllocConsole();
	freopen_s(&pConsole, "CONOUT$", "wb", stdout);
	background->loadTexture("background.dds");
	std::vector<Moo::Sprite *> ground;

	for (float i = 0; i < 20; ++i) {
		Moo::Sprite *tmpGround = new Moo::Sprite(40, 40, i * 40, 0);
		tmpGround->loadTexture("ground.dds");
		ground.push_back(tmpGround);
	}
	while (window.isOpen())
	{
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
		window.draw(background);
		for (auto _ground : ground) {
			window.draw(_ground);
		}
		window.draw(mario);
		window.display();
	}
	for (auto _ground : ground) {
		_ground->release();
	}
	mario->release();
	window.destroy();
	return 0;
}
