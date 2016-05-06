#pragma once

#include "Window.h"
#include "Game.h"
#include "Exceptions.h"
#include "Log.h"

#include <vector>

namespace Moo
{
	static void	testJsonParser()
	{
		// SETTINGS FILE
		JsonParser test = JsonParser("Settings.json");
		test.parseFile(FileType::SETTINGS);
		Settings settings = test.getSettingsFileContent();
		std::cout << "------------- BEGINNING OF TESTING SETTINGS FILE READER -------------" << std::endl << std::endl;
		std::cout << "Resolution: " << settings.getResolutionString() << std::endl;
		std::cout << "Volume: " << settings.getVolumeString() << std::endl;
		std::cout << "Fullscreen: " << settings.getIsFullscreenString() << std::endl;
		std::cout << "Fps: " << settings.getFpsString() << std::endl;
		//std::cout << "Keys Mapping: " << settings.getKeysMapping() << std::endl;
		test.saveSettings(settings, "Settings.json");
		std::cout << std::endl << "------------- END OF TESTING SETTINGS FILE READER -------------" << std::endl << std::endl;
		// MAP FILE
		std::cout << "------------- BEGINNING OF TESTING MAP FILE READER -------------" << std::endl << std::endl;
		test.setFilePath("Maps/TestHeatZones.json");
		test.parseFile(FileType::MAP);
		MapInfos map = test.parseMap();
		map.displayMapInfos();
		std::cout << std::endl << "------------- END OF TESTING MAP FILE READER -------------" << std::endl;

		system("pause");
	}
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	//Console
#ifdef _DEBUG
	FILE * pConsole;
	AllocConsole();
	freopen_s(&pConsole, "CONOUT$", "wb", stdout);
	freopen_s(&pConsole, "CONOUT$", "wb", stderr);
#endif // DEBUG

	try
	{
		//Getting the game window
		auto window = std::make_shared<Moo::Window>(hInstance, Moo::WindowSettings("Water Drop", Moo::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT)));
		window->setFpsLimit(FPS_LIMIT);
		Moo::Game::getInstance().startGame(window);

		//Moo::testJsonParser();
	}
	catch (std::string &e)
	{
		std::cout << e << std::endl;
	}

	/*
	try {
	//Main game loop
	}
	catch (Moo::InitException &e) {
	std::cerr << "CRITICAL_ERROR: " << e.what() << std::endl;
	LOG(Moo::Log::CRITICAL_ERROR) << e.what() << std::endl;
	}
	*/
	/*
	catch (Moo::Exception &e) {
	std::cerr << "WARNING: " << e.what() << std::endl;
	Moo::Log().put(Moo::Log::WARNING) << e.what() << std::endl;
	}
	*/

	return 0;
}