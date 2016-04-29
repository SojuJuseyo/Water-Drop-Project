#pragma once

#include "../Includes/Window.h"
#include "../Includes/Game.h"
#include "../Includes/Exceptions.h"
#include "../Includes/Log.h"

#include <vector>

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) 
{
	//Console
	FILE * pConsole;
	AllocConsole();
	freopen_s(&pConsole, "CONOUT$", "wb", stdout);
	freopen_s(&pConsole, "CONOUT$", "wb", stderr);

	//Getting the game window
	auto window = std::make_shared<Moo::Window>(hInstance, Moo::WindowSettings("Water Drop", Moo::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT)));
	window->setFpsLimit(FPS_LIMIT);

	try {
		//Main game loop
		Moo::Game::getInstance().initScenes(window);
	}
	catch (Moo::InitException &e) {
		std::cerr << "CRITICAL_ERROR: " << e.what() << std::endl;
		LOG(Moo::Log::CRITICAL_ERROR) << e.what() << std::endl;
	}
	/*
	catch (Moo::Exception &e) {
		std::cerr << "WARNING: " << e.what() << std::endl;
		Moo::Log().put(Moo::Log::WARNING) << e.what() << std::endl;
	}
	*/

	return 0;
}
