#include "Game.h"
#include "log.h"
/*
todo :

gere SOIT tout les loading au debut SOIT chaque scene est load quand on en a besoin

gerer la scene precedente pour faire un return

chaque scene est une class et contient son init

chaque scene infinite loop pour gerer leur contenu, il faut faire en sort que les scene useless ne soit pas execute, il faut que


son :
d3d::getInstance().getCamera()->setPosition(camera.getPosition());
audio.playSound(music, true);

a appeller quune seule fois par scene

a chaque run scene il faut reupt la posisiton de la camera par une posisiuton stocke dans la scene en elle meme
*/

namespace Moo
{
	Game::Game()
	{
		_soundSystem = std::make_shared<SoundSystem>();
	}

	Game::~Game()
	{
	}

	Game&			Game::getInstance()
	{
		static Game instance;
		return instance;
	}

	void			Game::resetScene(e_scene sceneType)
	{
		for (auto &scene : _listOfScenes) {
			if (scene.sceneType == sceneType) {
				scene.scene->init(_window);
				return;
			}
		}
	}

	void			Game::resetAllScenes()
	{
		for (auto &scene : _listOfScenes)
		{
			if (scene.scene != nullptr) {
				scene.scene->init(_window);
				Moo::d3d::getInstance().getCamera()->reset();
			}
		}
	}

	// a appeller qu'une fois au debut pour initialiser les Scenes
	void			Game::initScenes(std::shared_ptr<Moo::Window> theUsedWindow)
	{
		_window = theUsedWindow;
		createScene(MAIN_MENU, new Menu());
		createScene(PAUSE_MENU, new MenuPause());
		createScene(CONTROLS_MENU, new ControleScene());
		createScene(LEVEL1, new LevelScene());
		for (auto &scene : _listOfScenes)
		{
			if (scene.scene != nullptr) {
				scene.scene->init(_window);
			}
		}
		runScene(MAIN_MENU);
		_isGameRunning = true;
		while (_isGameRunning) {
			update();
			if (!theUsedWindow->isOpen()) {
				backToPrevScene();
			}
		}
	}
	
	void			Game::exit()
	{
		_isGameRunning = false;
	}

	// a appeller quand on veut passer d'une scene a l'autre.
	void			Game::runScene(e_scene type)
	{
		std::cout << "RUN SCENE " << type << " NOMBER OF SCENES : " << _listOfScenes.size() << std::endl;
		s_scene *tmpSceneForPrev = _currentScene;
		s_scene *tmpScene = getSceneByType(type);
		if (tmpScene != nullptr) {
			_currentScene = tmpScene;
		}
		else {
			return;
		}
		Moo::d3d::getInstance().getCamera()->reset();
		_currentScene->prevScene = tmpSceneForPrev; 
		if ((int)type >= (int)LEVEL1) {
			d3d::getInstance().getCamera()->setPosition(dynamic_cast<LevelScene *>(_currentScene->scene)->getCamera().getPosition());
			_currentScene->prevScene = getSceneByType(Game::PAUSE_MENU);
			if (((LevelScene*)_currentScene->scene)->themeChan != nullptr)
				((LevelScene*)_currentScene->scene)->themeChan->setPaused(false);
		}
		if (type == MAIN_MENU) {
			_currentScene->prevScene = nullptr;
		}
	}

	void			Game::backToPrevScene()
	{
		if (_currentScene != nullptr && _currentScene->prevScene != nullptr) {
			runScene(_currentScene->prevScene->sceneType);
		}
	}

	void			Game::goToNextScene()
	{
		if (_currentScene != nullptr && (int)_currentScene->sceneType >= (int)LEVEL1) {
			if ((int)_currentScene->sceneType < (int)NUMBER_OF_SCENE - 1) {
				runScene((e_scene)((int)_currentScene->sceneType + 1));
			}
			else {
				runScene(MAIN_MENU);
			}
		}
	}

	std::shared_ptr<SoundSystem> Game::getSoundSystem()
	{
		return _soundSystem;
	}

	bool			Game::update()
	{
		if (_currentScene != nullptr && _currentScene->scene != nullptr) {
			if (!_currentScene->scene->runUpdate()) {
				exit();
			}
		}
		return false;
	}

	void			Game::createScene(e_scene sceneType, Scene* sceneRef)
	{
		s_scene newScene;
		newScene.scene = sceneRef;
		newScene.sceneType = sceneType;
		newScene.prevScene = nullptr;
		_listOfScenes.push_back(newScene);
	}

	Game::s_scene*		Game::getSceneByType(e_scene sceneType)
	{
		for (auto &scene : _listOfScenes) {
			if (scene.sceneType == sceneType) {
				return &scene;
			}
		}
		return nullptr;
	}
}