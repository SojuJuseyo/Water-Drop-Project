#pragma once

#include "Window.h"
#include "Game.h"

#include <vector>

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) 
{
	//Console
	FILE * pConsole;
	AllocConsole();
	freopen_s(&pConsole, "CONOUT$", "wb", stdout);

	//Getting the game window
	Moo::Window window(hInstance, Moo::WindowSettings("Water Drop", Moo::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT)));

	//Main game loop
	Moo::Game game = Moo::Game::getInstance();
	game.initScenes();

	//60 FPS master race
	window.setFpsLimit(FPS_LIMIT);

	try {
		game.run(window);
	} catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}
