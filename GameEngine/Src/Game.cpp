#include "GameManagmentHeader.h"
#include "log.h"

namespace Moo
{
	Game::Game()
	{
		_soundSystem = std::make_shared<SoundSystem>();
		_textures["Player"].loadFromFile(GRAPHICS_PATH + std::string("player.dds"));
		_textures["Background_Controle"].loadFromFile(GRAPHICS_PATH + std::string("controle.dds"));
		_textures["Background_Menu"].loadFromFile(GRAPHICS_PATH + std::string("Menu_WTP_DDS.dds"));
		_textures["Hitbox"].loadFromFile(GRAPHICS_PATH + std::string("hitbox.dds"));
		_textures["Background_Menu_Pause"].loadFromFile(GRAPHICS_PATH + std::string("Menu_Pause_WTP_DDS.dds"));
		_textures["Enemy"].loadFromFile(GRAPHICS_PATH + std::string("enemy.dds"));
		_textures["Tileset"].loadFromFile(GRAPHICS_PATH + std::string("tileset.dds"));
		_textures["Background"].loadFromFile(GRAPHICS_PATH + std::string("background.dds"));
		_textures["Interface"].loadFromFile(GRAPHICS_PATH + std::string("interfaceTest.dds"));
		// Temp texture for the bullet
		_textures["Bullet"].loadFromFile(GRAPHICS_PATH + std::string("enemy.dds"));
		_textures["Lose"].loadFromFile(GRAPHICS_PATH + std::string("You_Lost_DDS.dds"));
		_textures["Win"].loadFromFile(GRAPHICS_PATH + std::string("You_Won_DDS.dds"));
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
		for (auto &scene : _listOfScenes)
		{
			if (scene.sceneType == _currentScene->sceneType && (int)_currentScene->sceneType >= (int)LEVEL1)
			{
				((LevelScene *)(scene.scene))->clean();
				d3d::getInstance().getCamera()->setInfoMap(dynamic_cast<LevelScene *>(scene.scene)->getCamera().getInfoMap());
				d3d::getInstance().getCamera()->setPosition(dynamic_cast<LevelScene *>(scene.scene)->getCamera().getPosition());
				break;
			}
		}
	}

	// fait un init sur toute les scenes (sauf la scene du loading screen) et reset la camera generale
	void			Game::resetAllScenes()
	{
		for (int index = 1; index < (int)_listOfScenes.size(); ++index)
		{
			if (_listOfScenes[index].scene != nullptr)
				_listOfScenes[index].scene->init(_window, _textures);
		}
		Moo::d3d::getInstance().getCamera()->reset();
	}

	// a appeller qu'une fois au debut pour initialiser les Scenes + lance automatiquement l'execution du jeu en lancant MAIN MENU + contient la game loop
	void			Game::startGame(std::shared_ptr<Moo::Window> theUsedWindow)
	{
		_window = theUsedWindow;
		createScene(LOADING, new LoadingScene());
		displayLoadingScreen();
		createScene(MAIN_MENU, new Menu());
		createScene(PAUSE_MENU, new MenuPause());
		createScene(CONTROLS_MENU, new ControleScene());
		createScene(WIN, new WinScene());
		createScene(LEVEL1, new LevelScene("Maps/TestScript.json"));
		createScene(LEVEL2, new LevelScene("Maps/TheBreach.json"));
		createScene(LEVEL3, new LevelScene("Maps/Shoot.json"));
		//createScene(LEVEL4, new LevelScene("Maps/Raining.json"));
		//createScene(LEVEL5, new LevelScene("Maps/Yamakasi.json"));
		//createScene(LEVEL6, new LevelScene("Maps/TempleRun.json"));
		//createScene(LEVEL7, new LevelScene("Maps/TheElevator.json"));
		resetAllScenes();
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
		std::cout << "RUN SCENE " << type << " NUMBER OF SCENE : " << _listOfScenes.size() << std::endl;
		s_scene *tmpSceneForPrev = _currentScene;
		s_scene *tmpScene = getSceneByType(type);
		if (tmpScene != nullptr)
			_currentScene = tmpScene;
		else
			return;
		Moo::d3d::getInstance().getCamera()->reset();
		if ((int)type >= (int)LEVEL1) {
			if (!isContinue)
				cleanCurrentScene();
			d3d::getInstance().getCamera()->setInfoMap(dynamic_cast<LevelScene *>(_currentScene->scene)->getCamera().getInfoMap());
			d3d::getInstance().getCamera()->setPosition(dynamic_cast<LevelScene *>(_currentScene->scene)->getCamera().getPosition());
			_currentScene->prevScene = getSceneByType(Game::PAUSE_MENU);
			if (((LevelScene*)_currentScene->scene)->themeChan != nullptr)
				((LevelScene*)_currentScene->scene)->themeChan->setPaused(false);
		}
		if ((type == PAUSE_MENU && (int)(tmpSceneForPrev->sceneType) >= (int)LEVEL1) || type == CONTROLS_MENU)
			_currentScene->prevScene = tmpSceneForPrev;
		if (type == MAIN_MENU)
			_currentScene->prevScene = nullptr;
	}

	// retour en arriere sert a pauser le jeu, et revenir en arriere dans les menu principaux
	void			Game::backToPrevScene()
	{
		if (_currentScene != nullptr && _currentScene->prevScene != nullptr)
			runScene(_currentScene->prevScene->sceneType, true);
		else if (_currentScene != nullptr && _currentScene->sceneType == WIN)
			runScene(MAIN_MENU, false);
	}

	// charge la scene de jeu suivant
	void			Game::goToNextScene()
	{
		if (_currentScene != nullptr && (int)_currentScene->sceneType >= (int)LEVEL1) {
			if ((int)_currentScene->sceneType < (int)NUMBER_OF_SCENE - 1)
				runScene((e_scene)((int)_currentScene->sceneType + 1), false);
			else
				runScene(WIN, false);
		}
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
		_listOfScenes.push_back(newScene);
	}

	// renvoie la reference de la scene via son type (parmi les scenes crees)
	Game::s_scene*		Game::getSceneByType(e_scene sceneType)
	{
		for (auto &scene : _listOfScenes) {
			if (scene.sceneType == sceneType)
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
}