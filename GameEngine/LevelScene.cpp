#include "LevelScene.h"

namespace Moo
{
	LevelScene::LevelScene()
	{

	}

	LevelScene::~LevelScene()
	{

	}

	void LevelScene::clean()
	{		
		std::cout << "Clearing entities lists" << std::endl;
		for (auto statEnt : _staticEntities)
			statEnt.second.reset();
		_staticEntities.clear();
		std::cout << "Static entities list is cleared, size: " << _staticEntities.size() << std::endl;
		for (auto dynEnt : _dynamicEntities)
			dynEnt.second.reset();
		_dynamicEntities.clear();
		std::cout << "Dynamic entities list is cleared, size: " << _dynamicEntities.size() << std::endl;
		_player.reset();
		_background.reset();
		std::cout << "Level scene is cleared" << std::endl;
	}

	void	LevelScene::loadFromSpriteSheet()
	{
		_spriteSheet["Block"] = SpriteRect(16.f, 16.f, 128.f, 16.f);
		_spriteSheet["Platform"] = SpriteRect(16.f, 16.f, 128.f, 16.f);
		_spriteSheet["Ground"] = SpriteRect(16.f, 16.f, 128.f, 16.f);
		_spriteSheet["Exit"] = SpriteRect(16.f, 16.f, 128.f, 16.f);

		_spriteSheet["Block"].makeVertexTab(4, 0);
		_spriteSheet["Platform"].makeVertexTab(0, 0);
		_spriteSheet["Ground"].makeVertexTab(1, 0);
		_spriteSheet["Exit"].makeVertexTab(5, 0);
	}

	void	LevelScene::getEntitiesFromMap(JsonParser *map)
	{
		_textures["Player"].loadFromFile("character.dds");
		_textures["Enemy"].loadFromFile("enemy.dds");
		_textures["Block"].loadFromFile("tileset.dds");
		_textures["Platform"].loadFromFile("tileset.dds");
		_textures["Ground"].loadFromFile("tileset.dds");
		_textures["Exit"].loadFromFile("tileset.dds");
		loadFromSpriteSheet();

		//All the data contained in the map
		std::list<Tile *> playerTiles = map->getMap().getTilesFromColor("#ffabcdef"); //blue
		std::list<Tile *> platformTiles = map->getMap().getTilesFromColor("#fff93738"); //red
		std::list<Tile *> bottomTiles = map->getMap().getTilesFromColor("#ff117050"); //green
		std::list<Tile *> enemyTiles = map->getMap().getTilesFromColor("#ff000000"); //black
		std::list<Tile *> blockTiles = map->getMap().getTilesFromColor("#ff551A8B"); //purple
		std::list<Tile *> exitTiles = map->getMap().getTilesFromColor("#ffffd700"); //gold

		//Because the map created by the map editor are not in WINDOW_HEIGHT * WINDOW_WIDTH resolution
		/*float multHeight = WINDOW_HEIGHT / map->getMap().getMapHeight();
		float multWidth = WINDOW_WIDTH / map->getMap().getMapWidth();

		std::cout << "multHeight: " << multHeight << std::endl;
		std::cout << "multWidth: " << multWidth << std::endl;*/

		//counter
		int i = 1;

		//Player specs
		float playerHeight = 48.4f;
		float playerWidth = 48.4f;
		float playerMass = 300;

		//Enemies specs
		float enemiesHeight = 40;
		float enemiesWidth = 40;
		float enemiesMass = 100;

		//Enemies
		for (auto enemyTile : enemyTiles)
		{
			Moo::Sprite *enemySprite = new Moo::Sprite(enemiesWidth, enemiesHeight, enemyTile->getPosX() * 40, enemyTile->getPosY() * 40);
			enemySprite->loadTexture(&_textures["Enemy"]);
			auto enemy = std::make_shared<Moo::Character>(Moo::Vector2f(1, 0), enemiesMass, enemySprite, true, 4.f, false);
			enemy->setCollision(true);
			// To make sure that enemies have less health than us at the beginning
			enemy->setHealth(4);
			enemySprite->scale(Moo::Vector2f(-0.1f, -0.1f));
			enemy->getHitboxSprite()->setScale(enemy->getSprite()->getScale());
			_dynamicEntities.push_back(std::make_pair("Enemy " + std::to_string(i), enemy));
			++i;
		}

		//reset counter
		i = 1;

		//platforms
		for (auto platformTile : platformTiles)
		{
			Moo::Sprite *platform = new Moo::Sprite(40, 40, platformTile->getPosX() * 40, platformTile->getPosY() * 40);
			platform->loadTexture(&_textures["Platform"], &_spriteSheet["Platform"]);
			auto platformEntity = std::make_shared<Moo::Character>(Moo::Vector2f(1, 0), 0.f, platform, false, 0.f, false);
			_staticEntities.push_back(std::make_pair("Platform " + std::to_string(i), platformEntity));
			++i;
		}

		//bloc
		for (auto blockTile : blockTiles)
		{
			Moo::Sprite *block = new Moo::Sprite(40, 40, blockTile->getPosX() * 40, blockTile->getPosY() * 40);
			block->loadTexture(&_textures["Block"], &_spriteSheet["Block"]);
			auto blocEntity = std::make_shared<Moo::Character>(Moo::Vector2f(1, 0), 0.f, block, false, 0.f, false);
			_staticEntities.push_back(std::make_pair("Block", blocEntity));
		}

		//bottom
		for (auto bottomTile : bottomTiles)
		{
			Moo::Sprite *ground = new Moo::Sprite(40, 40, bottomTile->getPosX() * 40, bottomTile->getPosY() * 40);
			ground->loadTexture(&_textures["Ground"], &_spriteSheet["Ground"]);
			auto groundEntity = std::make_shared<Moo::Character>(Moo::Vector2f(1, 0), 0.f, ground, false, 0.f, false);
			_staticEntities.push_back(std::make_pair("Bottom", groundEntity));
		}

		//exit
		for (auto exitTile : exitTiles)
		{
			Moo::Sprite *exit = new Moo::Sprite(40, 40, exitTile->getPosX() * 40, exitTile->getPosY() * 40);
			exit->loadTexture(&_textures["Exit"], &_spriteSheet["Exit"]);
			auto exitEntity = std::make_shared<Moo::Character>(Moo::Vector2f(1, 0), 0.f, exit, false, 0.f, false);
			_staticEntities.push_back(std::make_pair("Exit " + std::to_string(i), exitEntity));
			++i;
		}

		if (playerTiles.size() > 0)
		{
			//Get the first element because there is only one player
			std::list<Tile *>::const_iterator playerIt = playerTiles.begin();

			//Player
			Moo::Sprite *character = new Moo::Sprite(playerWidth, playerHeight, (*playerIt)->getPosX() * 40, (*playerIt)->getPosY() * 40);
			character->loadTexture(&_textures["Player"]);
			auto player = std::make_shared<Moo::Character>(Moo::Vector2f(0, 0), playerMass, character, true, 6.f, true);
			//The player is always the first of the entities vector
			_dynamicEntities.insert(_dynamicEntities.begin(), std::make_pair("Player", player));
		}
	}

	Camera LevelScene::getCamera()
	{
		return _camera;
	}

	bool	LevelScene::init(std::shared_ptr<Window> window)
	{
		std::cout << "Starting init" << std::endl;
		this->clean();
		_window = window;
		
		_textures["Background"].loadFromFile("background.dds");

		//We get the map
		//map = new JsonParser("2d-Maps/50x50.json");
		//map = new JsonParser("2d-Maps/MapPreAlpha.json");
		_map = JsonParser("2d-Maps/MapPlaytestSession.json");

		if (_map.parseFile() == -1)
			throw std::exception("Can't load the map");

		//map->getMap().displayMapInfos();

		//Read the entities from the map
		getEntitiesFromMap(&_map);

		std::cout << "Succeeded in getting entities from the map" << std::endl;
		std::cout << "Static entities list is filled, size: " << _staticEntities.size() << std::endl;
		std::cout << "Dynamic entities list is filled, size: " << _dynamicEntities.size() << std::endl;

		//background
		_background = std::make_shared<Moo::Sprite>(4000.f, 3000.f, 0.f, 0.f);
		_background->loadTexture(&_textures["Background"]);

		_player = std::static_pointer_cast<Moo::Character>(_dynamicEntities[0].second);

		// Temp texture for the bullet
		_textures["Bullet"].loadFromFile("character.dds");
		_textures["Lose"].loadFromFile("You_Lost_DDS.dds");
		_textures["Win"].loadFromFile("You_Won_DDS.dds");
		Moo::d3d::getInstance().getCamera()->setInfoMap(_map.getMap());
		_camera.reset();
		_lose = std::make_shared<Moo::Sprite>(400.f, 133.f, 0.f, 0.f);
		_lose->loadTexture(&_textures["Lose"]);
		_win = std::make_shared<Moo::Sprite>(400.f, 133.f, 0.f, 0.f);
		_win->loadTexture(&_textures["Win"]);

		//init sound system
		_soundSystem = Game::getInstance().getSoundSystem();

		if (themeChan == nullptr)
		{
			if (_soundSystem->addSound(_map.getMap().getMapAudioFile().c_str(), "custom") == false)
			{
				std::cout << _map.getMap().getMapAudioFile() << std::endl;
				std::cout << "music failed" << std::endl;
				themeChan = nullptr;
			}
			//themeChan = _soundSystem->playSound("custom", true);
		}
		if (themeChan != nullptr)
			themeChan->setPaused(true);

		_player->setTimers();
		_startTime = std::chrono::system_clock::now();
		_canTemporarilyJump = _startTime;
		_lastJump = _startTime;

		std::cout << "Init successful" << std::endl;

		return (true);
	}

	void	LevelScene::inputHandling()
	{
		//Reseting _triedJump to check if the player tries to wall jump this frame
		_triedJump = false;
		_exitReached = false;
		_playerDead = false;

		Moo::Keyboard::updateInput();

		if (Moo::Keyboard::isPressed(Moo::Keyboard::B))
			if (themeChan != nullptr)
				themeChan->setPaused(false);

		if (Moo::Keyboard::isPressed(Moo::Keyboard::C))
			if (themeChan != nullptr)
				themeChan->setPaused(true);

		//Cheats
		if (Moo::Keyboard::isDown(Moo::Keyboard::GodMode))
			_player->toggleGodMode();

		if (Moo::Keyboard::isDown(Moo::Keyboard::SizeUp))
			_player->changeHealth(1);

		if (Moo::Keyboard::isDown(Moo::Keyboard::SizeDown))
			_player->changeHealth(-1);

		if (Moo::Keyboard::isDown(Moo::Keyboard::Space))
		{
			bool wallJump = false;
			if (_player->getVelocity().y > 0)
			{
				std::chrono::duration<double> elapsed_seconds_wallJump = std::chrono::system_clock::now() - _canTemporarilyJump;
				std::chrono::duration<double> elapsed_seconds_lastJump = std::chrono::system_clock::now() - _lastJump;
				if (elapsed_seconds_lastJump.count() > 0.2 && elapsed_seconds_wallJump.count() < 0.1)
				{
					std::cout << "The player tried to jump" << std::endl;
					wallJump = true;
					if (_player->getVelocity().x < 0)
						_player->setWallJumpVelocity(true);
					else
						_player->setWallJumpVelocity(false);
				}
				else
					std::cout << "Too late to wall jump, elapsed seconds count: " << elapsed_seconds_wallJump.count() << std::endl;
			}
			if (_player->jump(wallJump) == true)
			{
				_soundSystem->playSound("jump", false);
				_canTemporarilyJump = _startTime;
				_lastJump = std::chrono::system_clock::now();
			}
		}

		if (Moo::Keyboard::isPressed(Moo::Keyboard::Left))
			_player->move(Direction::LEFT);

		if (Moo::Keyboard::isPressed(Moo::Keyboard::Right))
			_player->move(Direction::RIGHT);

		if (Moo::Keyboard::isDown(Moo::Keyboard::Shot))
		{
			if (_player->getHealth() > 1)
			{
				_soundSystem->playSound("jump", false);
				// Define the base pos of the bullet and create the sprite
				float bulletPosX = _player->getSprite()->getX() + (_player->getSprite()->getWidth());
				float bulletPosY = _player->getSprite()->getY() + (_player->getSprite()->getHeight() / 2);
				Moo::Sprite *bulletSprite = new Moo::Sprite(15.f, 15.f, bulletPosX, bulletPosY);

				bulletSprite->loadTexture(&_textures["Bullet"]);

				// Creation of the bullet
				auto bullet = std::make_shared<Moo::Bullet>(bulletSprite, false);
				bullet->setCollision(true);

				// Addition of the bullet to the bullet pool
				_dynamicEntities.push_back(std::pair<std::string, std::shared_ptr<Moo::Entity>>("bullet", bullet));
				// Check if cheat code is activated.
				if (_player->isGodMode() == false)
					_player->changeHealth(-1);
				std::cout << "Player health : " << _player->getHealth() << std::endl;
			}
			else
				std::cout << "Player is too small to shoot" << std::endl;
		}
	}

	void	LevelScene::displayHitboxesAndSprites()
	{
		_window->clear();
		_window->draw(_background.get());

		// Display hitbox if godmode is on
		if (_player->isGodMode() == true)
			_window->draw(_player->getHitboxSprite());

		//Draw static entities and their hitboxes
		for (auto entity : _staticEntities)
		{
			_window->draw(std::static_pointer_cast<Moo::Character>(entity.second)->getSprite());
			_window->draw(std::static_pointer_cast<Moo::Character>(entity.second)->getHitboxSprite());
		}

		//Draw dynamic entities and their hitboxes
		for (auto entity : _dynamicEntities)
		{
			_window->draw(std::static_pointer_cast<Moo::Character>(entity.second)->getSprite());
			_window->draw(std::static_pointer_cast<Moo::Character>(entity.second)->getHitboxSprite());
			if (_strnicmp(entity.first.c_str(), "Enemy", 5) == 0)
				std::static_pointer_cast<Moo::Character>(entity.second)->getSprite()->rotate(1);
		}
	}

	void	LevelScene::exitReached()
	{
		_win->setPosition(((Moo::d3d::getInstance().getCamera()->getPosition().x * -1) +
						  (Moo::d3d::getInstance().getScreenSize().x / 2 - 200)),
						 ((Moo::d3d::getInstance().getCamera()->getPosition().y * -1) +
						  (Moo::d3d::getInstance().getScreenSize().y / 2))
			);
		if (themeChan != nullptr)
			themeChan->setPaused(true);
		FMOD::Channel *chan = _soundSystem->playSound("victory", false);
		_window->draw(_win.get());
		_window->display();
		Sleep(3000);
		chan->stop();
		_camera.reset();
		Moo::d3d::getInstance().getCamera()->reset();
		Game::getInstance().resetScene(Game::LEVEL1);
		Game::getInstance().runScene(Game::MAIN_MENU);
	}

	void	LevelScene::playerDead()
	{
		_lose->setPosition(((Moo::d3d::getInstance().getCamera()->getPosition().x * -1) +
						   (Moo::d3d::getInstance().getScreenSize().x / 2 - 250)),
						  ((Moo::d3d::getInstance().getCamera()->getPosition().y * -1) +
						   (Moo::d3d::getInstance().getScreenSize().y / 2))
			);
		if (themeChan != nullptr)
			themeChan->setPaused(true);
		FMOD::Channel *chan = _soundSystem->playSound("defeat", false);
		_window->draw(_lose.get());
		_window->display();
		Sleep(3000);
		chan->stop();
		_camera.reset();
		Moo::d3d::getInstance().getCamera()->reset();
		Game::getInstance().resetScene(Game::LEVEL1);
		Game::getInstance().runScene(Game::LEVEL1);
	}

	void	LevelScene::applyGravityAndCollisions()
	{
		//Init collison & gravity loop values
		HitZone hitZone;
		bool deletedBullet;
		bool deletedCharacter;
		bool isPlayer;
		Vector2f decal(0, 0);
		
		for (auto dynEntIt = _dynamicEntities.begin(); dynEntIt != _dynamicEntities.end();)
		{
			decal = Vector2f(0, 0);
			if ((*dynEntIt).second == _player)
			{
				isPlayer = true;
				if (_player->getHealth() > 1)
					_player->checkEvaporation();
			}
			else
				isPlayer = false;
			(*dynEntIt).second->setGravity(true);

			if (_strnicmp((*dynEntIt).first.c_str(), "Bullet", 6) == 0)
				(*dynEntIt).second->setVelocity(Vector2f(STANDARD_VELOCITY_X * 2, (*dynEntIt).second->getVelocity().y));

			if ((*dynEntIt).second->getGravity() == true)
			{
				(std::static_pointer_cast<Moo::Character>((*dynEntIt).second))->update();
				(std::static_pointer_cast<Moo::Character>((*dynEntIt).second))->resetHitbox();
			}

			deletedBullet = false;
			deletedCharacter = false;

			for (auto statEntIt = _staticEntities.begin();
				 statEntIt != _staticEntities.end();
				 ++statEntIt)
			{
				if ((hitZone = (*dynEntIt).second->collisionAABB((*statEntIt).second.get())) != HitZone::NONE)
				{
					//If player collides with an Exit
					if (isPlayer == true && _strnicmp((*statEntIt).first.c_str(), "Exit", 4) == 0)
					{
						_exitReached = true;
						break;
					}
					//If we collide with a wall/platform/bottom
					else if (isPlayer == true || (_strnicmp((*dynEntIt).first.c_str(), "Enemy", 5) == 0))
					{
						if (hitZone == HitZone::RIGHT_SIDE)
							decal.x = (*statEntIt).second->getHitbox().x1 - (*dynEntIt).second->getHitbox().x2;
						else if (hitZone == HitZone::LEFT_SIDE)
							decal.x = (*statEntIt).second->getHitbox().x2 - (*dynEntIt).second->getHitbox().x1;
						else if (hitZone == HitZone::TOP)
						{
							decal.y = (*statEntIt).second->getHitbox().y2 - (*dynEntIt).second->getHitbox().y1;
							(*dynEntIt).second->setVelocity(Vector2f((*dynEntIt).second->getVelocity().x, -1));
						}
						else if (hitZone == HitZone::BOTTOM)
						{
							decal.y = (*statEntIt).second->getHitbox().y1 - (*dynEntIt).second->getHitbox().y2;
							std::static_pointer_cast<Moo::Character>((*dynEntIt).second)->resetPos();
							(*dynEntIt).second->setGravity(false);
						}
					}
					else if (_strnicmp((*dynEntIt).first.c_str(), "Bullet", 6) == 0)
					{
						std::cout << "Deleting " << (*dynEntIt).first << std::endl;
						dynEntIt = _dynamicEntities.erase(dynEntIt);
						deletedBullet = true;
						break;
					}
				}
			}

			if (deletedBullet == false && _exitReached == false)
			{
				auto character = std::static_pointer_cast<Moo::Character>((*dynEntIt).second);
				if (decal.y != 0)
					character->getSprite()->setY(character->getSprite()->getY() + decal.y);
				if (decal.x != 0)
				{
					_canTemporarilyJump = std::chrono::system_clock::now();
					character->getSprite()->setX(character->getSprite()->getX() + decal.x);
				}
				character->resetHitbox();

				for (auto SecondDynEntIt = _dynamicEntities.begin();
					 SecondDynEntIt != _dynamicEntities.end();
					 ++SecondDynEntIt)
				{
					if (!(_strnicmp((*dynEntIt).first.c_str(), "Bullet", 6) == 0 && _strnicmp((*SecondDynEntIt).first.c_str(), "Bullet", 6) == 0)
						&& (*SecondDynEntIt).second.get() != character.get()
					 && ((hitZone = character->collisionAABB((*SecondDynEntIt).second.get())) != HitZone::NONE))
					{
						//If we collide with an enemy : Absorb him
						std::cout << "Collision between " << (*dynEntIt).first << " and " << (*SecondDynEntIt).first << std::endl;
						if (_strnicmp((*SecondDynEntIt).first.c_str(), "Enemy", 5) == 0)
						{
							auto enemyCollided = std::static_pointer_cast<Moo::Character>((*SecondDynEntIt).second);
							if (_strnicmp((*dynEntIt).first.c_str(), "Bullet", 6) == 0)
							{
								dynEntIt = _dynamicEntities.erase(dynEntIt);
								deletedBullet = true;
								enemyCollided->changeHealth(1);
								std::cout << (*SecondDynEntIt).first << " health: " << enemyCollided->getHealth() << std::endl;
								break;
							}
							else 
							{
								if (character->getHealth() >= enemyCollided->getHealth() || character->isGodMode() == true)
								{
									character->changeHealth(enemyCollided->getHealth() * 33 / 100);
									std::cout << (*dynEntIt).first << " health: " << character->getHealth() << std::endl;
									SecondDynEntIt = _dynamicEntities.erase(SecondDynEntIt);
									deletedCharacter = true;
									break;
								}
								else if (isPlayer == true)
								{
									_playerDead = true;
									break;
								}
								else
								{
									enemyCollided->changeHealth(character->getHealth() * 33 / 100);
									std::cout << (*SecondDynEntIt).first << " health: " << enemyCollided->getHealth() << std::endl;
									dynEntIt = _dynamicEntities.erase(dynEntIt);
									deletedCharacter = true;
									break;
								}
							}
						}
					}
				}
			}
			if (deletedBullet == false && deletedCharacter == false)
				++dynEntIt;
			else if (deletedCharacter == true || _playerDead == true || _exitReached == true)
				break;
		}
		if (_playerDead == true)
			this->playerDead();
		if (_exitReached == true)
			this->exitReached();
	}

	bool	LevelScene::runUpdate()
	{
		/*
		if (themeChan != nullptr)
			themeChan->setPaused(false);
		*/

		//Getting the inputs of the player
		inputHandling();

		//Applying gravity to dynamic entities and checking all collisions
		applyGravityAndCollisions();

		//Reseting the positon of the camera
		Moo::d3d::getInstance().getCamera()->update(_player->getHitbox());
		_camera = *Moo::d3d::getInstance().getCamera();

		//Display the game elements
		displayHitboxesAndSprites();

		//Drawing all that is inside the window
		_window->display();

		/*
		if (themeChan != nullptr)
			themeChan->setPaused(true);
		*/
		return true;
	}
}