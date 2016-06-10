#include "GameManagmentHeader.h"
#include "log.h"

#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>
#pragma comment(lib, "User32.lib")

namespace Moo
{
	Game::Game()
	{
		_soundSystem = std::make_shared<SoundSystem>();
		_textures["Player"].loadFromFile(GRAPHICS_PATH + std::string("playerJump.dds"));
		_textures["Background_Controle"].loadFromFile(GRAPHICS_PATH + std::string("controls.dds"));
		_textures["Background_Credits"].loadFromFile(GRAPHICS_PATH + std::string("credits.dds"));
		_textures["Hitbox"].loadFromFile(GRAPHICS_PATH + std::string("hitbox.dds"));
		_textures["Enemy"].loadFromFile(GRAPHICS_PATH + std::string("enemy.dds"));
		_textures["Tileset"].loadFromFile(GRAPHICS_PATH + std::string("tileset.dds"));
		_textures["Background"].loadFromFile(GRAPHICS_PATH + std::string("background.dds"));
		_textures["HeatZone"].loadFromFile(GRAPHICS_PATH + std::string("heat.dds"));
		_textures["Drop"].loadFromFile(GRAPHICS_PATH + std::string("HUD.dds"));

		_textures["Lose"].loadFromFile(GRAPHICS_PATH + std::string("defeatScreen.dds"));
		_textures["Win"].loadFromFile(GRAPHICS_PATH + std::string("victoryScreen.dds"));
		_textures["End"].loadFromFile(GRAPHICS_PATH + std::string("theEnd.dds"));
		_textures["Bullet"].loadFromFile(GRAPHICS_PATH + std::string("bullet.dds"));

		//Menu related textures
		_textures["Menu_Background"].loadFromFile(GRAPHICS_PATH + std::string("Menu/background.dds"));
		_textures["Menu_Title"].loadFromFile(GRAPHICS_PATH + std::string("Menu/title.dds"));
		_textures["Menu_Play"].loadFromFile(GRAPHICS_PATH + std::string("Menu/PLAY.dds"));
		_textures["Menu_Play_On"].loadFromFile(GRAPHICS_PATH + std::string("Menu/PLAY On.dds"));
		_textures["Menu_HowToPlay"].loadFromFile(GRAPHICS_PATH + std::string("Menu/How to play.dds"));
		_textures["Menu_HowToPlay_On"].loadFromFile(GRAPHICS_PATH + std::string("Menu/How to play On.dds"));
		_textures["Menu_Options"].loadFromFile(GRAPHICS_PATH + std::string("Menu/Options.dds"));
		_textures["Menu_Options_On"].loadFromFile(GRAPHICS_PATH + std::string("Menu/Options On.dds"));
		_textures["Menu_Credits"].loadFromFile(GRAPHICS_PATH + std::string("Menu/Credits.dds"));
		_textures["Menu_Credits_On"].loadFromFile(GRAPHICS_PATH + std::string("Menu/Credits On.dds"));
		_textures["Menu_Quit"].loadFromFile(GRAPHICS_PATH + std::string("Menu/Quit Game.dds"));
		_textures["Menu_Quit_On"].loadFromFile(GRAPHICS_PATH + std::string("Menu/Quit Game On.dds"));

		//Pause Menu related textures
		_textures["Pause_Menu_Title"].loadFromFile(GRAPHICS_PATH + std::string("Menu/Pause.dds"));
		_textures["Pause_Menu_Resume"].loadFromFile(GRAPHICS_PATH + std::string("Menu/Resume Game.dds"));
		_textures["Pause_Menu_Resume_On"].loadFromFile(GRAPHICS_PATH + std::string("Menu/Resume Game On.dds"));
		_textures["Pause_Menu_Back_To_Menu"].loadFromFile(GRAPHICS_PATH + std::string("Menu/Back to menu.dds"));
		_textures["Pause_Menu_Back_To_Menu_On"].loadFromFile(GRAPHICS_PATH + std::string("Menu/back to menu On.dds"));

		//Settings related textures
		_textures["Settings_Background"].loadFromFile(GRAPHICS_PATH + std::string("Settings/background.dds"));
		_textures["Settings_Title"].loadFromFile(GRAPHICS_PATH + std::string("Settings/Settings.dds"));
		_textures["Settings_Fullscreen"].loadFromFile(GRAPHICS_PATH + std::string("Settings/Fullscreen.dds"));
		_textures["Settings_Fullscreen_On"].loadFromFile(GRAPHICS_PATH + std::string("Settings/Fullscreen On.dds"));
		_textures["Settings_Music"].loadFromFile(GRAPHICS_PATH + std::string("Settings/Music.dds"));
		_textures["Settings_Music_On"].loadFromFile(GRAPHICS_PATH + std::string("Settings/Music On.dds"));
		_textures["Settings_Sound_Effects"].loadFromFile(GRAPHICS_PATH + std::string("Settings/Sound Effects.dds"));
		_textures["Settings_Sound_Effects_On"].loadFromFile(GRAPHICS_PATH + std::string("Settings/Sound Effects On.dds"));
		_textures["Settings_Back"].loadFromFile(GRAPHICS_PATH + std::string("Settings/Back.dds"));
		_textures["Settings_Back_On"].loadFromFile(GRAPHICS_PATH + std::string("Settings/Back On.dds"));
		_textures["Settings_Save"].loadFromFile(GRAPHICS_PATH + std::string("Settings/Save.dds"));
		_textures["Settings_Save_On"].loadFromFile(GRAPHICS_PATH + std::string("Settings/Save On.dds"));
		_textures["Settings_Checkbox_Unchecked"].loadFromFile(GRAPHICS_PATH + std::string("Settings/case.dds"));
		_textures["Settings_Checkbox_Checked"].loadFromFile(GRAPHICS_PATH + std::string("Settings/casecochee.dds"));

		_gameTime = nullptr;
		//Loading related textures
		_textures["Loading"].loadFromFile(GRAPHICS_PATH + std::string("loading.dds"));

		_textures["LevelNameBackground"].loadFromFile(GRAPHICS_PATH + std::string("levelNameBackground.dds"));
	}

	Game::~Game()
	{
	}

	Game&			Game::getInstance()
	{
		static Game instance;
		return instance;
	}

	// fait un clean sur la scene actuelle
	void			Game::cleanCurrentScene()
	{
		std::cout << "cleanCurrentScene called" << std::endl;
		if (_currentScene != nullptr && _currentScene->sceneType == LEVEL) {
			_currentScene->scene->clean();
			d3d::getInstance().getCamera()->setInfoMap(dynamic_cast<LevelScene *>(_currentScene->scene)->getCamera().getInfoMap());
			d3d::getInstance().getCamera()->setPosition(dynamic_cast<LevelScene *>(_currentScene->scene)->getCamera().getPosition());
		}
	}

	// fait un init sur toute les scenes (sauf la scene du loading screen) et reset la camera generale
	void			Game::resetAllScenes()
	{
		std::cout << "resetAllScenes called" << std::endl;
		for (int index = 1; index < (int)_listOfScenes.size(); ++index)
		{
			if (_listOfScenes[index].scene != nullptr)
			{
				displayLoadingScreen();
				try
				{
					std::cout << "try to init scene " << _listOfScenes[index].sceneType << " :" << std::endl;
					_listOfScenes[index].scene->init(_window, _textures);
					std::cout << "scene inited" << std::endl;
				}
				catch (Exception e)
				{
					// sus quand le init d'un map a failed
					std::cout << "INIT FAILED FOR SCENE INDEX : " << index << std::endl;
				}
				displayLoadingScreen();
			}
		}
		Moo::d3d::getInstance().getCamera()->reset();
		std::cout << "resetAllScenes ends" << std::endl;
	}

	// a appeller qu'une fois au debut pour initialiser les Scenes + lance automatiquement l'execution du jeu en lancant MAIN MENU + contient la game loop
	void			Game::startGame(std::shared_ptr<Moo::Window> theUsedWindow)
	{
		_window = theUsedWindow;
		createScene(LOADING, new LoadingScene());
		createScene(MAIN_MENU, new Menu());
		createScene(PAUSE_MENU, new MenuPause());
		createScene(HOWTOPLAY_MENU, new ControleScene());
		createScene(SETTINGS_MENU, new SettingsScreen());
		createScene(CREDITS, new CreditsScene());
		createScene(WIN, new WinScene());
		displayLoadingScreen();
		readMapFiles();
		displayLoadingScreen();
		_levelCounter = 0;
		resetAllScenes();
		displayLoadingScreen();
		runScene(MAIN_MENU, false);
		_isGameRunning = true;
		while (_isGameRunning) {
			update();
			if (!theUsedWindow->isOpen())
				exit();
		}
	}

	// call de l'exit pour stoper la game loop
	void			Game::exit()
	{
		_isGameRunning = false;
	}

	// a appeller quand on veut passer d'une scene a l'autre.
	void			Game::runScene(e_scene type, bool isContinue)
	{
		std::cout << "RUN SCENE " << type  << std::endl;
		s_scene *tmpSceneForPrev = _currentScene;
		s_scene *tmpScene = getSceneByType(type);
		if (tmpScene != nullptr)
			_currentScene = tmpScene;
		else
			return;
		Moo::d3d::getInstance().getCamera()->reset();
		if (type == LEVEL) {
			if (_gameTime == nullptr)
				_gameTime = new Timer;
			if (!isContinue)
				cleanCurrentScene();
			d3d::getInstance().getCamera()->setInfoMap(dynamic_cast<LevelScene *>(_currentScene->scene)->getCamera().getInfoMap());
			d3d::getInstance().getCamera()->setPosition(dynamic_cast<LevelScene *>(_currentScene->scene)->getCamera().getPosition());
			_currentScene->prevScene = getSceneByType(Game::PAUSE_MENU);
			if (((LevelScene*)_currentScene->scene)->themeChan != nullptr)
				((LevelScene*)_currentScene->scene)->themeChan->setPaused(false);
		}
		if ((type == PAUSE_MENU && tmpSceneForPrev->sceneType == LEVEL) || type == HOWTOPLAY_MENU || type == SETTINGS_MENU || type == CREDITS)
			_currentScene->prevScene = tmpSceneForPrev;
		if (type == MAIN_MENU) {
			delete _gameTime;
			_gameTime = nullptr;
			_levelCounter = 0;
			_currentScene->prevScene = nullptr;
		}
	}

	// retour en arriere sert a pauser le jeu, et revenir en arriere dans les menu principaux
	void			Game::backToPrevScene()
	{
		std::cout << "backToPrevScene called" << std::endl;
		if (_currentScene != nullptr && _currentScene->prevScene != nullptr)
			runScene(_currentScene->prevScene->sceneType, true);
		else if (_currentScene != nullptr && _currentScene->sceneType == WIN)
		{
			_currentScene->scene->clean();
			runScene(MAIN_MENU, false);
		}
	}

	// charge la scene de jeu suivant
	void			Game::goToNextScene()
	{
		std::cout << "goToNextScene called" << std::endl;
		if (_currentScene != nullptr && _currentScene->sceneType == LEVEL && _currentScene->level < _nbOfLevels) {
			++_levelCounter;
			if (((LevelScene *)_currentScene->scene)->themeChan != nullptr)
				((LevelScene *)_currentScene->scene)->themeChan->setPaused(true);
			runScene(LEVEL, false);
		}
		if (_currentScene != nullptr && _currentScene->sceneType == LEVEL && _levelCounter >= _nbOfLevels)
			runScene(WIN, false);
		else if (_currentScene != nullptr && _currentScene->sceneType == WIN)
			runScene(MAIN_MENU, false);
	}

	std::shared_ptr<SoundSystem> Game::getSoundSystem()
	{
		return _soundSystem;
	}

	// boucle d'update (game loop)
	bool			Game::update()
	{
		//std::cout << "fps:" << (1.0f / Moo::Fps::getInstance().getFrameTime()) << std::endl;
		if (_currentScene != nullptr && _currentScene->scene != nullptr) {
			if (Moo::Keyboard::isDown(Moo::Keyboard::Escape))
				backToPrevScene();
			if (Moo::Keyboard::isDown(Moo::Keyboard::P) && _currentScene->sceneType == LEVEL)
				goToNextScene();
			if (!_currentScene->scene->runUpdate())
				exit();
		}
		return false;
	}

	// cree une structure scene (incluant la reference de la scene et son type) et push dans la liste des scenes
	void			Game::createScene(e_scene sceneType, Scene* sceneRef)
	{
		s_scene newScene;
		newScene.scene = sceneRef;
		newScene.sceneType = sceneType;
		newScene.prevScene = nullptr;
		newScene.level = _levelCounter;
		_listOfScenes.push_back(newScene);
		if (sceneType == LEVEL)
			++_levelCounter;
	}

	// renvoie la reference de la scene via son type (parmi les scenes crees)
	Game::s_scene*		Game::getSceneByType(e_scene sceneType)
	{
		for (auto &scene : _listOfScenes) {
			if ((scene.sceneType == sceneType && sceneType != LEVEL) ||
				(scene.sceneType == sceneType && sceneType == LEVEL && scene.level == _levelCounter))
				return &scene;
		}
		return nullptr;
	}

	// init et affiche le loading screen
	void Game::displayLoadingScreen()
	{
		for (auto &scene : _listOfScenes)
		{
			if (scene.sceneType == LOADING)
			{
				if (scene.scene->_hasBeenInited == false)
					scene.scene->init(_window, _textures);
				scene.scene->runUpdate();
				return;
			}
		}
	}

	void Game::readMapFiles()
	{
		WIN32_FIND_DATA ffd;
		LARGE_INTEGER filesize;
		TCHAR szDir[MAX_PATH];
		size_t length_of_arg;
		HANDLE hFind = INVALID_HANDLE_VALUE;
		DWORD dwError = 0;
		std::string path = GetMapFolder();
		StringCchLength(path.c_str(), MAX_PATH, &length_of_arg);
		StringCchCopy(szDir, MAX_PATH, path.c_str());
		StringCchCat(szDir, MAX_PATH, TEXT("\\*"));
		hFind = FindFirstFile(szDir, &ffd);
		if (INVALID_HANDLE_VALUE == hFind)
			return ;
		do{
			if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)){
				filesize.LowPart = ffd.nFileSizeLow;
				filesize.HighPart = ffd.nFileSizeHigh;
				if (isFileNameOk(std::string(ffd.cFileName)))
				{
					std::cout << "mapfile : " << ffd.cFileName << std::endl;
					std::string mapFileName = std::string(ffd.cFileName);
					createScene(LEVEL, new LevelScene("Maps/" + mapFileName));
					++_nbOfLevels;
				}
			}
		}
		while (FindNextFile(hFind, &ffd) != 0);
		dwError = GetLastError();
		if (dwError != ERROR_NO_MORE_FILES)
			return;
		FindClose(hFind);
		return;
	}

	std::string Game::GetMapFolder()
	{
		char buffer[MAX_PATH];
		GetModuleFileName(NULL, buffer, MAX_PATH);
		std::string::size_type pos = std::string(buffer).find_last_of("\\/");
		std::string path = std::string(buffer).substr(0, pos) + MAP_FILES_PATH;
		std::cout << "PATH : " << path << std::endl;
		return path;
	}

	bool Game::isFileNameOk(std::string fileName)
	{
		std::string fileType = ".json";
		std::string enfFile = fileName.substr(fileName.size() - fileType.size(), fileType.size());
		if (enfFile.compare(fileType) == 0)
			return true;
		return false;
	}
}