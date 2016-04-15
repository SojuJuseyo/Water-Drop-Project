#pragma once

#include "Window.h"
#include "Game.h"
#include "Exceptions.h"
#include "Log.h"

#include <vector>

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) 
{
	//Console
	FILE * pConsole;
	AllocConsole();
	freopen_s(&pConsole, "CONOUT$", "wb", stdout);
	freopen_s(&pConsole, "CONOUT$", "wb", stderr);

	//Getting the game window
	Moo::Window window(hInstance, Moo::WindowSettings("Water Drop", Moo::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT)));
	Moo::Game game = Moo::Game::getInstance();
	try {
		//Main game loop
		game.initScenes();
		//60 FPS master race
		window.setFpsLimit(FPS_LIMIT);

		game.run(window);
	}
	catch (Moo::InitException &e) {
		std::cerr << "CRITICAL_ERROR: " << e.what() << std::endl;
		Moo::Log().put(Moo::Log::CRITICAL_ERROR) << e.what() << std::endl;
	}
	catch (Moo::Exception &e) {
		std::cerr << "WARNING: " << e.what() << std::endl;
		Moo::Log().put(Moo::Log::WARNING) << e.what() << std::endl;
	}

	return 0;
}
