#include "LevelScene.h"

namespace Moo
{
	LevelScene::LevelScene(const std::string &pathMapFile)
	{
		_pathMapFile = pathMapFile;
		_entityTypeName[EntityType::PLAYER] = "Player";
		_entityTypeName[EntityType::ENEMY] = "Enemy";
		_entityTypeName[EntityType::BULLET] = "Bullet";
		_entityTypeName[EntityType::BLOCK] = "Block";
		_entityTypeName[EntityType::PLATFORM] = "Platform";
		_entityTypeName[EntityType::GROUND] = "Ground";
		_entityTypeName[EntityType::EXIT] = "Exit";
		_entityTypeName[EntityType::ENTRANCE] = "Entrance";
	}

	LevelScene::~LevelScene()
	{
	}

	std::string	LevelScene::getEntityTypeName(EntityType type)
	{
		return 	_entityTypeName[type];
	}

	void LevelScene::clean()
	{
		std::cout << "Clearing entities lists" << std::endl;
		for (auto statEnt : _staticEntities)
			statEnt.reset();
		_staticEntities.clear();
		std::cout << "Static entities list is cleared, size: " << _staticEntities.size() << std::endl;
		for (auto dynEnt : _dynamicEntities)
			dynEnt.reset();
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

	void	LevelScene::fillStaticEntitiesList(EntityType type, float posX, float posY)
	{
		auto sprite = std::make_shared<Moo::Sprite>(40.f, 40.f, posX * 40, posY * 40);
		sprite->loadTexture(&_textures[getEntityTypeName(type)], &_spriteSheet[getEntityTypeName(type)]);
		auto staticEntity = std::make_shared<Moo::StaticEntity>(sprite, type, false);
		_staticEntities.push_back(staticEntity);
	}

	void	LevelScene::fillDynamicEntitiesList(int mult, EntityType type, float posX, float posY, float width, float height, float mass, float health, bool isCharacter)
	{
		auto sprite = std::make_shared<Moo::Sprite>(width, height, posX * mult, posY * mult);
		sprite->loadTexture(&_textures[getEntityTypeName(type)]);

		if (isCharacter == true)
		{
			auto dynamicEntity = std::make_shared<Moo::Character>(Moo::Vector2f(0, 0), mass, sprite, true, health, type);
			if (type == EntityType::PLAYER)
				_dynamicEntities.insert(_dynamicEntities.begin(), dynamicEntity);
			else
				_dynamicEntities.push_back(dynamicEntity);
		}
		else
		{
			auto dynamicEntity = std::make_shared<Moo::Bullet>(sprite, mass, health);
			_dynamicEntities.push_back(dynamicEntity);
		}
	}

	void	LevelScene::getEntitiesFromMap(MapInfos map)
	{
		_textures["Player"].loadFromFile(GRAPHICS_PATH + std::string("character.dds"));
		_textures["Enemy"].loadFromFile(GRAPHICS_PATH + std::string("enemy.dds"));
		_textures["Block"].loadFromFile(GRAPHICS_PATH + std::string("tileset.dds"));
		_textures["Platform"].loadFromFile(GRAPHICS_PATH + std::string("tileset.dds"));
		_textures["Ground"].loadFromFile(GRAPHICS_PATH + std::string("tileset.dds"));
		_textures["Exit"].loadFromFile(GRAPHICS_PATH + std::string("tileset.dds"));
		loadFromSpriteSheet();

		//All the data contained in the map
		std::list<Tile *> blockTiles = map.getTilesFromSprite("0");
		std::list<Tile *> bottomTiles = map.getTilesFromSprite("1");
		std::list<Tile *> enemyTiles = map.getTilesFromSprite("3");
		std::list<Tile *> platformTiles = map.getTilesFromSprite("4");
		std::list<Tile *> playerTiles = map.getTilesFromSprite("5");
		std::list<Tile *> exitTiles = map.getTilesFromSprite("6");

		//platforms
		for (auto platformTile : platformTiles)
			fillStaticEntitiesList(EntityType::PLATFORM, platformTile->getPosX(), platformTile->getPosY());

		//bloc
		for (auto blockTile : blockTiles)
			fillStaticEntitiesList(EntityType::BLOCK, blockTile->getPosX(), blockTile->getPosY());

		//bottom
		for (auto bottomTile : bottomTiles)
			fillStaticEntitiesList(EntityType::GROUND, bottomTile->getPosX(), bottomTile->getPosY());

		//exit
		for (auto exitTile : exitTiles)
			fillStaticEntitiesList(EntityType::EXIT, exitTile->getPosX(), exitTile->getPosY());

		//Enemies specs
		float enemiesHeight = 40;
		float enemiesWidth = 40;
		float enemiesHealth = 4.f;
		float enemiesMass = 100;

		//Enemies
		for (auto enemyTile : enemyTiles)
			fillDynamicEntitiesList(40, EntityType::ENEMY, enemyTile->getPosX(), enemyTile->getPosY(), enemiesWidth, enemiesHeight, enemiesMass, enemiesHealth, true);

		//Player specs
		float playerHeight = 48.4f;
		float playerWidth = 48.4f;
		float playerHealth = 6.f;
		float playerMass = 300;

		if (playerTiles.size() > 0)
		{
			//Get the first element because there is only one player
			std::list<Tile *>::const_iterator playerIt = playerTiles.begin();
			fillDynamicEntitiesList(40, EntityType::PLAYER, (*playerIt)->getPosX(), (*playerIt)->getPosY(), playerWidth, playerHeight, playerMass, 6.f, true);
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

		_textures["Background"].loadFromFile(GRAPHICS_PATH + std::string("background.dds"));

		//We get the map
		JsonParser fileParser = JsonParser(_pathMapFile);

		fileParser.parseFile(FileType::MAP);
		_map = fileParser.parseMap();

		//Read the entities from the map
		getEntitiesFromMap(_map);

		std::cout << "Succeeded in getting entities from the map" << std::endl;
		std::cout << "Static entities list is filled, size: " << _staticEntities.size() << std::endl;
		std::cout << "Dynamic entities list is filled, size: " << _dynamicEntities.size() << std::endl;

		//background
		_background = std::make_shared<Moo::Sprite>(4000.f, 3000.f, 0.f, 0.f);
		_background->loadTexture(&_textures["Background"]);

		_player = std::static_pointer_cast<Moo::Character>(_dynamicEntities[0]);

		// Temp texture for the bullet
		_textures["Bullet"].loadFromFile(GRAPHICS_PATH + std::string("character.dds"));
		_textures["Lose"].loadFromFile(GRAPHICS_PATH + std::string("You_Lost_DDS.dds"));
		_textures["Win"].loadFromFile(GRAPHICS_PATH + std::string("You_Won_DDS.dds"));
		Moo::d3d::getInstance().getCamera()->setInfoMap(_map);
		_camera.reset();
		_lose = std::make_shared<Moo::Sprite>(400.f, 133.f, 0.f, 0.f);
		_lose->loadTexture(&_textures["Lose"]);
		_win = std::make_shared<Moo::Sprite>(400.f, 133.f, 0.f, 0.f);
		_win->loadTexture(&_textures["Win"]);

		//init sound system
		_soundSystem = Game::getInstance().getSoundSystem();

		if (themeChan == nullptr)
		{
			if (_soundSystem->addSound(_map.getMapAudioFile().c_str(), "custom") == false)
			{
				std::cout << _map.getMapAudioFile() << std::endl;
				std::cout << "music failed" << std::endl;
				themeChan = nullptr;
			}
			themeChan = _soundSystem->playSound("custom", true);
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
			if (_player->getGravity() == true)
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
				_soundSystem->playSound("shoot", false);

				fillDynamicEntitiesList(1, EntityType::BULLET,
					_player->getSprite()->getX() + _player->getSprite()->getWidth(),
					_player->getSprite()->getY() + (_player->getSprite()->getHeight() / 2),
					15.f, 15.f, 100.f, 1.f, false);

				// Check if cheat code is activated.
				if (_player->isGodMode() == false)
					_player->changeHealth(-1.f);
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
			_window->draw(entity->getSprite());
			_window->draw(entity->getHitboxSprite());
		}

		//Draw dynamic entities and their hitboxes
		for (auto entity : _dynamicEntities)
		{
			_window->draw(entity->getSprite());
			_window->draw(entity->getHitboxSprite());
			if (entity->getEntityType() == EntityType::ENEMY)
				entity->getSprite()->rotate(1);
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
		Game::getInstance().goToNextScene();
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
		Game::getInstance().cleanCurrentScene();
	}

	void	LevelScene::applyGravityAndCollisions()
	{
		//Init collison & gravity loop values
		HitZone hitZone;
		bool deletedBullet, deletedCharacter, isInHeatZone;
		Vector2f decal(0, 0);

		for (auto dynEntIt = _dynamicEntities.begin(); dynEntIt != _dynamicEntities.end();)
		{
			decal = Vector2f(0, 0);

			if ((*dynEntIt)->getEntityType() == EntityType::PLAYER && _player->getHealth() > 1)
				_player->checkEvaporation();

			(*dynEntIt)->setGravity(true);

			if ((*dynEntIt)->getEntityType() == EntityType::BULLET)
				(*dynEntIt)->setVelocity(Vector2f(STANDARD_VELOCITY_X * 2, (*dynEntIt)->getVelocity().y));

			if ((*dynEntIt)->getGravity() == true)
			{
				(std::static_pointer_cast<Moo::Character>((*dynEntIt)))->update();
				(*dynEntIt)->resetHitbox();
			}

			deletedBullet = false;
			deletedCharacter = false;
			isInHeatZone = false;

			for (auto statEntIt = _staticEntities.begin(); statEntIt != _staticEntities.end(); ++statEntIt)
			{
				if ((hitZone = (*dynEntIt)->collisionAABB((*statEntIt).get())) != HitZone::NONE)
				{
					//If player collides with an Exit
					if ((*dynEntIt)->getEntityType() == EntityType::PLAYER && (*statEntIt)->getEntityType() == EntityType::EXIT)
					{
						_exitReached = true;
						break;
					}
					//If we collide with a wall/platform/bottom
					else if ((*dynEntIt)->getEntityType() == EntityType::PLAYER || ((*dynEntIt)->getEntityType() == EntityType::ENEMY))
					{
						if (hitZone == HitZone::RIGHT_SIDE)
							decal.x = (*statEntIt)->getHitbox().x1 - (*dynEntIt)->getHitbox().x2;
						else if (hitZone == HitZone::LEFT_SIDE)
							decal.x = (*statEntIt)->getHitbox().x2 - (*dynEntIt)->getHitbox().x1;
						else if (hitZone == HitZone::TOP)
						{
							decal.y = (*statEntIt)->getHitbox().y2 - (*dynEntIt)->getHitbox().y1;
							(*dynEntIt)->setVelocity(Vector2f((*dynEntIt)->getVelocity().x, -1));
						}
						else if (hitZone == HitZone::BOTTOM)
						{
							decal.y = (*statEntIt)->getHitbox().y1 - (*dynEntIt)->getHitbox().y2;
							(*dynEntIt)->resetPos();
							(*dynEntIt)->setGravity(false);
						}
					}
					else if ((*dynEntIt)->getEntityType() == EntityType::BULLET)
					{
						std::cout << "Deleting " << getEntityTypeName((*dynEntIt)->getEntityType()) << std::endl;
						dynEntIt = _dynamicEntities.erase(dynEntIt);
						deletedBullet = true;
						break;
					}
					isInHeatZone = (*statEntIt)->getIsHeatZone();
				}
			}

			if (deletedBullet == false && _exitReached == false)
			{
				if (decal.y != 0)
					(*dynEntIt)->getSprite()->setY((*dynEntIt)->getSprite()->getY() + decal.y);
				if (decal.x != 0)
				{
					_canTemporarilyJump = std::chrono::system_clock::now();
					(*dynEntIt)->getSprite()->setX((*dynEntIt)->getSprite()->getX() + decal.x);
				}
				(*dynEntIt)->resetHitbox();
				if (isInHeatZone == true)
					(*dynEntIt)->evaporateHeatZone();

				for (auto SecondDynEntIt = _dynamicEntities.begin(); SecondDynEntIt != _dynamicEntities.end(); ++SecondDynEntIt)
				{
					if (!((*dynEntIt)->getEntityType() == EntityType::BULLET && (*SecondDynEntIt)->getEntityType() == EntityType::BULLET)
						&& (*SecondDynEntIt).get() != (*dynEntIt).get()
						&& ((hitZone = (*dynEntIt)->collisionAABB((*SecondDynEntIt).get())) != HitZone::NONE))
					{
						//If we collide with an enemy : Absorb him
						std::cout << "Collision between " << getEntityTypeName((*dynEntIt)->getEntityType()) << " and " << getEntityTypeName((*SecondDynEntIt)->getEntityType()) << std::endl;
						if ((*SecondDynEntIt)->getEntityType() == EntityType::ENEMY)
						{
							if ((*dynEntIt)->getEntityType() == EntityType::BULLET)
							{
								(*SecondDynEntIt)->changeHealth((*dynEntIt)->getHealth());
								std::cout << getEntityTypeName((*SecondDynEntIt)->getEntityType()) << " health: " << (*SecondDynEntIt)->getHealth() << std::endl;
								std::cout << "Deleting " << getEntityTypeName((*dynEntIt)->getEntityType()) << std::endl;
								dynEntIt = _dynamicEntities.erase(dynEntIt);
								deletedBullet = true;
								break;
							}
							else if ((*dynEntIt)->getHealth() >= (*SecondDynEntIt)->getHealth() || std::static_pointer_cast<Moo::Character>(*dynEntIt)->isGodMode() == true)
							{
								if ((*dynEntIt)->getEntityType() == EntityType::PLAYER)
									_soundSystem->playSound("powerup", false);
								(*dynEntIt)->changeHealth((*SecondDynEntIt)->getHealth() * 33 / 100);
								std::cout << getEntityTypeName((*dynEntIt)->getEntityType()) << " health: " << (*dynEntIt)->getHealth() << std::endl;
								std::cout << "Deleting " << getEntityTypeName((*SecondDynEntIt)->getEntityType()) << std::endl;
								SecondDynEntIt = _dynamicEntities.erase(SecondDynEntIt);
								deletedCharacter = true;
								break;
							}
							else if ((*dynEntIt)->getEntityType() == EntityType::PLAYER)
							{
								_playerDead = true;
								break;
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