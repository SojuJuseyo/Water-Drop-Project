#pragma once

#include "Window.h"
#include "Game.h"

#include <vector>

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) 
{
	//To display std::cout output
	FILE * pConsole;
	AllocConsole();
	freopen_s(&pConsole, "CONOUT$", "wb", stdout);

	//Getting the game window
	Moo::Window window(hInstance, Moo::WindowSettings("Water Drop"));

	//Main game loop
	Moo::Game game;

	//60 FPS master race
	window.setFpsLimit(FPS_LIMIT);

	game.run(window);
	return 0;
}
