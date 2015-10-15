#pragma once
#include "Window.h"
#include "Keyboard.h"
#include "d3d.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Moo::Window window(hInstance, Moo::WindowSettings("test"));
	Moo::RectangleShape *rectangle = new Moo::RectangleShape(200, 200, 200, 200, DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));

	while (window.isOpen())
	{
		if (Moo::Keyboard::isPressed(Moo::Keyboard::Left))
		{

		}
		window.clear();
		window.draw(rectangle);
		window.display();
	}
	window.destroy();
	return 0;
}
