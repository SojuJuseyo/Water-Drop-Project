#pragma once
#include "Window.h"
#include "Keyboard.h"
#include "d3d.h"
#include <sstream>
#include "Fps.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Moo::Window window(hInstance, Moo::WindowSettings("test"));
	Moo::RectangleShape *rectangle = new Moo::RectangleShape(50, 50, 200, 200, DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));

	window.setFpsLimit(60);
	FILE * pConsole;; AllocConsole();
	freopen_s(&pConsole, "CONOUT$", "wb", stdout);
	while (window.isOpen())
	{
		std::cout << "FPS: " << window.getFps() << std::endl;
		if (Moo::Keyboard::isPressed(Moo::Keyboard::Left)) {
			rectangle->move(-1, 0);
		}
		else if (Moo::Keyboard::isPressed(Moo::Keyboard::Right)) {
			rectangle->move(1, 0);
		}
		window.clear();
		window.draw(rectangle);
		window.display();
	}
	window.destroy();
	return 0;
}
