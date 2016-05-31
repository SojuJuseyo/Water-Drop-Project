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
		loadFromSpriteSheet();
	}

	LevelScene::~LevelScene()
	{
	}

	std::string	LevelScene::getEntityTypeName(EntityType type)
	{
		return 	_entityTypeName[type];
	}

	void	LevelScene::clearEntityType(EntityType type, bool activatedMustBeFalse)
	{
		for (auto dynEntIt = _dynamicEntities.begin(); dynEntIt != _dynamicEntities.end();)
			if ((*dynEntIt)->getEntityType() == type
			&& (activatedMustBeFalse == false
			|| (activatedMustBeFalse == true && (*dynEntIt)->getIsActivated() == false)))
				dynEntIt = _dynamicEntities.erase(dynEntIt);
			else
				++dynEntIt;
	}

	void	LevelScene::clean()
	{
		std::cout << "---------- Reseting level ----------" << std::endl << std::endl;

		bool needToClearBullets = false;
		//Reset all characters
		for (auto dynamicEntity : _dynamicEntities)
			if (dynamicEntity->getEntityType() != EntityType::BULLET)
				(std::static_pointer_cast<Moo::Character>(dynamicEntity))->reset();
			else if (needToClearBullets == false)
				needToClearBullets = true;

		//If there are any bullets in the list, delete them
		if (needToClearBullets == true)
			clearEntityType(EntityType::BULLET, false);

		//Sound
		_soundSystem = Game::getInstance().getSoundSystem();
		if (themeChan == nullptr)
		{
			if (_soundSystem->addSound(_map->getMapAudioFile().c_str(), "custom") == false)
			{
				std::cout << _map->getMapAudioFile() << std::endl;
				std::cout << "music failed" << std::endl;
				themeChan = nullptr;
			}
			themeChan = _soundSystem->playSound("custom", true);
		}
		if (themeChan != nullptr)
			themeChan->setPaused(true);

		//Various variables
		_player = std::static_pointer_cast<Moo::Character>(_dynamicEntities[0]);
		_player->setTimers();
		_startTime = std::chrono::system_clock::now();
		_canTemporarilyJump = _startTime;
		_lastJump = _startTime;
		_triedJump = false;
		_exitReached = false;
		_playerDead = false;
		_camera.resetToPlayer(_player->getHitbox());

		std::cout << std::endl << "---------- Level reseted ----------" << std::endl;
	}

	void	LevelScene::loadFromSpriteSheet()
	{
		_spriteSheet["Block"] = Moo::Vector2f(0, 0);
		_spriteSheet["Platform"] = Moo::Vector2f(4, 0);
		_spriteSheet["Ground"] = Moo::Vector2f(1, 0);
		_spriteSheet["Exit"] = Moo::Vector2f(6, 0);
	}

	void	LevelScene::fillStaticEntitiesList(EntityType type, Tile tile, bool isHeatZone)
	{
		auto sprite = std::make_shared<Moo::Sprite>(BLOCK_SIZE, BLOCK_SIZE, tile.getPosX() * BLOCK_SIZE, tile.getPosY() * BLOCK_SIZE);
		sprite->loadTexture(&_textures.get()->at("Tileset"));

		sprite->setRectFromSpriteSheet(_spriteSheet[getEntityTypeName(type)], Moo::Vector2f(48.f, 48.f));
		auto staticEntity = std::make_shared<Moo::StaticEntity>(sprite, type, isHeatZone, tile.getIsCollidable());
		if (tile.getProperties().getIsSet() == true)
		{
			staticEntity->setHitboxLastPos(
				(float)tile.getProperties().getX2() * BLOCK_SIZE,
				(float)tile.getProperties().getY2() * BLOCK_SIZE + sprite->getHeight(),
				(float)tile.getProperties().getX2() * BLOCK_SIZE + sprite->getWidth(),
				(float)tile.getProperties().getY2() * BLOCK_SIZE);
			staticEntity->setHitboxFirstPos(staticEntity->getHitbox());
			staticEntity->setIsScripted(true);
		}
		_staticEntities.push_back(staticEntity);
	}

	void	LevelScene::fillDynamicEntitiesList(EntityType type, float posX, float posY, float width, float height, float mass, float health, bool isCharacter, Direction direction, TileProperties properties)
	{
		float entitySize = BLOCK_SIZE;
		if (type == EntityType::BULLET)
			entitySize = 1;
		auto sprite = std::make_shared<Moo::Sprite>(width, height, posX * entitySize, posY * entitySize);

		sprite->loadTexture(&_textures.get()->at(getEntityTypeName(type)));
		if (type == EntityType::PLAYER)
			sprite->setRectFromSpriteSheet(Moo::Vector2f(1, 0), Moo::Vector2f(36, 42));
		if (type == EntityType::ENEMY)
			sprite->setRectFromSpriteSheet(Moo::Vector2f(0, 0), Moo::Vector2f(36, 42));
		if (isCharacter == true)
		{
			auto dynamicEntity = std::make_shared<Moo::Character>(Moo::Vector2f(0, 0), mass, sprite, true, health, type, direction);
			if (type == EntityType::PLAYER)
				_dynamicEntities.insert(_dynamicEntities.begin(), dynamicEntity);
			else
			{
				if (properties.getIsSet() == true)
				{
					dynamicEntity->setHitboxLastPos(
						(float)properties.getX2() * entitySize,
						(float)properties.getY2() * entitySize + sprite->getHeight(),
						(float)properties.getX2() * entitySize + sprite->getWidth(),
						(float)properties.getY2() * entitySize);
					dynamicEntity->setHitboxFirstPos(dynamicEntity->getHitbox());
					dynamicEntity->setIsScripted(true);
				}
				_dynamicEntities.push_back(dynamicEntity);
			}
		}
		else
		{
			auto dynamicEntity = std::make_shared<Moo::Bullet>(sprite, mass, health, direction);
			_dynamicEntities.push_back(dynamicEntity);
		}
	}

	void	LevelScene::createEnemy(Tile enemyTile, float characterHealth)
	{
		float multiplier = enemyTile.getProperties().getSize() / characterHealth;
		float enemyHeight = 42.f * multiplier;
		float enemyWidth = 36.f * multiplier;
		float enemyMass = 200.f * multiplier;
		fillDynamicEntitiesList(EntityType::ENEMY, enemyTile.getPosX(), enemyTile.getPosY(), enemyWidth, enemyHeight, enemyMass, (float)enemyTile.getProperties().getSize(), true, enemyTile.getProperties().getDirection(), enemyTile.getProperties());
	}

	void	LevelScene::getEntitiesFromMap(std::shared_ptr<MapInfos> map)
	{			
		//All the data contained in the map - dynamic
		std::list<Tile> enemyTiles = map->getTilesFromSprite("3");
		std::list<Tile> playerTiles = map->getTilesFromSprite("5");

		//All the data contained in the map - static
		std::list<Tile> blockTiles = map->getTilesFromSprite("0");
		std::list<Tile> bottomTiles = map->getTilesFromSprite("1");
		std::list<Tile> platformTiles = map->getTilesFromSprite("4");
		std::list<Tile> exitTiles = map->getTilesFromSprite("6");
		std::list<Tile> heatZonesTiles = map->getHeatZonesTileList();

		//platforms
		for (auto platformTile : platformTiles)
			fillStaticEntitiesList(EntityType::PLATFORM, platformTile, false);

		//bloc
		for (auto blockTile : blockTiles)
			fillStaticEntitiesList(EntityType::BLOCK, blockTile, false);

		//bottom
		for (auto bottomTile : bottomTiles)
			fillStaticEntitiesList(EntityType::GROUND, bottomTile, false);

		//exit
		for (auto exitTile : exitTiles)
			fillStaticEntitiesList(EntityType::EXIT, exitTile, false);

		//set if static entities are heat zones
		for (auto heatZoneTile : heatZonesTiles)
		{
			bool _wasInList = false;
			for (auto staticEntity : _staticEntities)
				if (staticEntity->getSprite()->getX() == heatZoneTile.getPosX() && staticEntity->getSprite()->getY() == heatZoneTile.getPosY())
				{
					_wasInList = true;
					staticEntity->setIsHeatZone(true);
				}
			if (_wasInList == false)
				fillStaticEntitiesList(EntityType::BLANK_HEAT_ZONE, heatZoneTile, true);
		}

		//Character specs
		float characterHeight = 42.f;
		float characterWidth = 36.f;
		float characterHealth = 4.f;
		float characterMass = 200;

		//Player specs
		float playerMultiplier = 1.5f;

		//Enemies
		for (auto enemyTile : enemyTiles)
		{
			createEnemy(enemyTile, characterHealth);
			/*std::cout << "Size: " << enemyTile.getProperties().getSize() << std::endl;
			if (enemyTile.getProperties().getSize() != 40)
				fillDynamicEntitiesList(48, EntityType::ENEMY, enemyTile.getPosX(), enemyTile.getPosY(), playerWidth, playerHeight, playerMass, playerHealth, true, enemyTile.getProperties().getDirection(), enemyTile.getProperties());
			else
				fillDynamicEntitiesList(40, EntityType::ENEMY, enemyTile.getPosX(), enemyTile.getPosY(), characterWidth, characterHeight, characterMass, characterHealth, true, enemyTile.getProperties().getDirection(), enemyTile.getProperties());*/
		}

		Tile playerTile = playerTiles.front();
		fillDynamicEntitiesList(EntityType::PLAYER, playerTile.getPosX(), playerTile.getPosY(),
								characterWidth * playerMultiplier, characterHeight * playerMultiplier, characterMass * playerMultiplier, characterHealth * playerMultiplier,
								true, playerTile.getProperties().getDirection(), playerTile.getProperties());
	}

	Camera	LevelScene::getCamera()
	{
		return _camera;
	}

	bool	LevelScene::init(std::shared_ptr<Window> window, std::map<std::string, Texture> textures)
	{
		std::cout << "---------- Starting init ----------" << std::endl << std::endl;
		_window = window;
		_textures = std::make_shared<std::map<std::string, Texture>>(textures);
		_font = std::make_shared<Font>();
		_font->loadFromFile("font.dds");
		_fps = std::make_shared<Text>("FPS XX", 2.f, 10.f, WINDOW_HEIGHT - 50.f, _font); // text;size;position.x;position.y;font

		//We get the map
		if (_map == nullptr)
		{
			JsonParser fileParser = JsonParser(_pathMapFile);

			fileParser.parseFile(FileType::MAP);
			_map = std::make_shared<MapInfos>(fileParser.parseMap());
		}

		//Read the entities from the map
		getEntitiesFromMap(_map);

		std::cout << "Succeeded in getting entities from the map" << std::endl;
		std::cout << "Static entities list is filled, size: " << _staticEntities.size() << std::endl;
		std::cout << "Dynamic entities list is filled, size: " << _dynamicEntities.size() << std::endl;

		//background
		_background = std::make_shared<Moo::Sprite>(4000.f, 3000.f, 0.f, 0.f);
		_background->loadTexture(&_textures.get()->at("Background"));

		_player = std::static_pointer_cast<Moo::Character>(_dynamicEntities[0]);

		_camera.setInfoMap(_map);
		_camera.resetToPlayer(_player->getHitbox());
		_lose = std::make_shared<Moo::Sprite>(400.f, 133.f, 0.f, 0.f);
		_lose->loadTexture(&_textures.get()->at("Lose"));

		_win = std::make_shared<Moo::Sprite>(400.f, 133.f, 0.f, 0.f);
		_win->loadTexture(&_textures.get()->at("Win"));

		_hud = std::make_shared<Moo::Sprite>(48.f, 48.f, 650.f, 550.f);
		_hud->loadTexture(&_textures.get()->at("Drop"));
		std::ostringstream oss;
		oss << _player->getHealth();
		_life = std::make_shared<Text>(oss.str(), 2.f, 700.f, 550.f, _font);

		//init sound system
		_soundSystem = Game::getInstance().getSoundSystem();

		if (themeChan == nullptr)
		{
			if (_soundSystem->addSound(_map->getMapAudioFile().c_str(), "custom") == false)
			{
				std::cout << _map->getMapAudioFile() << std::endl;
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
		_triedJump = false;
		_exitReached = false;
		_playerDead = false;

		std::cout << std::endl << "---------- Init successful ----------" << std::endl;

		return (true);
	}

	void	LevelScene::inputHandling()
	{
		//Reseting _triedJump to check if the player tries to wall jump this frame
		_triedJump = false;
		_exitReached = false;
		_playerDead = false;

		Moo::Keyboard::updateInput();

		if (Moo::Keyboard::isDown(Moo::Keyboard::A))
			std::cout << "Dynamic entities list size: " << _dynamicEntities.size() << std::endl;

		if (Moo::Keyboard::isDown(Moo::Keyboard::B))
			if (themeChan != nullptr)
				themeChan->setPaused(false);

		if (Moo::Keyboard::isDown(Moo::Keyboard::C))
			if (themeChan != nullptr)
				themeChan->setPaused(true);

		if (Moo::Keyboard::isDown(Moo::Keyboard::R))
			Moo::Game::getInstance().cleanCurrentScene();

		if (Moo::Keyboard::isDown(Moo::Keyboard::D))
			std::cout << "fps:" << _window->getFps() << std::endl;

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
		{
			if (_player->getDirection() != Direction::LEFT)
			{
				_player->setDirection(Direction::LEFT);
				_player->getSprite()->setRectFromSpriteSheet(Moo::Vector2f(0, 0), Moo::Vector2f(36, 42));
			}
			_player->move(Direction::LEFT);
		}

		if (Moo::Keyboard::isPressed(Moo::Keyboard::Right))
		{
			if (_player->getDirection() != Direction::RIGHT)
			{
				_player->setDirection(Direction::RIGHT);
				_player->getSprite()->setRectFromSpriteSheet(Moo::Vector2f(1, 0), Moo::Vector2f(36, 42));
			}
			_player->move(Direction::RIGHT);
		}

		if (Moo::Keyboard::isDown(Moo::Keyboard::Shot))
		{
			if (_player->getHealth() > 2.f)
			{
				_soundSystem->playSoundRandom("shoot");

				float startPosX;
				if (_player->getDirection() == Direction::RIGHT)
					startPosX = _player->getSprite()->getX() + _player->getSprite()->getWidth();
				else
					startPosX = _player->getSprite()->getX();

				TileProperties tmp;
				fillDynamicEntitiesList(EntityType::BULLET,
					startPosX,
					_player->getSprite()->getY() + (_player->getSprite()->getHeight() / 2),
					15.f, 15.f, 100.f, 1.f, false, _player->getDirection(), tmp);

				// Check if cheat code is activated.
				if (_player->isGodMode() == false)
					_player->changeHealth(-1.f);
				std::cout << "Player health : " << _player->getHealth() << std::endl;
			}
			else
				std::cout << "Player is too small to shoot" << std::endl;
		}
	}

	bool	LevelScene::isVisible(Entity baseEntity, Entity checkedEntity, float range)
	{
		if (checkedEntity.getHitbox().x1 < (baseEntity.getHitbox().x1 - range))
			return false;
		if (checkedEntity.getHitbox().x2 > (baseEntity.getHitbox().x2 + range))
			return false;
		if (checkedEntity.getHitbox().y1 > (baseEntity.getHitbox().y1 + range))
			return false;
		if (checkedEntity.getHitbox().y2 < (baseEntity.getHitbox().y2 - range))
			return false;
		return true;
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
			if (entity->getEntityType() != EntityType::BLANK_HEAT_ZONE)
				if (isVisible(*_player, *entity.get(), 800))
					_window->draw(entity->getSprite());
			//_window->draw(entity->getHitboxSprite());
		}

		//Draw dynamic entities and their hitboxes
		for (auto entity : _dynamicEntities)
			if (entity->getIsActivated() == true)
				if (isVisible(*_player, *entity.get(), 800))
				{
					if (entity->getEntityType() == EntityType::ENEMY)
					{
						if (entity->getIsScripted() == false)
							entity->getSprite()->rotate(1);
						if (_player->getHealth() > entity->getHealth() || _player->isGodMode())
							entity->getSprite()->setRectFromSpriteSheet(Vector2f((float)entity->getDirection(), 1), Vector2f(36, 42));
						else
							entity->getSprite()->setRectFromSpriteSheet(Vector2f((float)entity->getDirection(), 0), Vector2f(36, 42));
					}
					_window->draw(entity->getSprite());
					//_window->draw(entity->getHitboxSprite());
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
		_window->draw(_win.get());
		_window->display();
		_soundSystem->playSoundTilEnd("victory");
		Game::getInstance().goToNextScene();
	}

	void	LevelScene::playerDead()
	{
		_lose->setPosition(((Moo::d3d::getInstance().getCamera()->getPosition().x * -1) +
			(Moo::d3d::getInstance().getScreenSize().x / 2 - 200)),
			((Moo::d3d::getInstance().getCamera()->getPosition().y * -1) +
				(Moo::d3d::getInstance().getScreenSize().y / 2))
			);
		if (themeChan != nullptr)
			themeChan->setPaused(true);
		_window->draw(_lose.get());
		_window->display();
		_soundSystem->playSoundTilEnd("defeat");
		Game::getInstance().cleanCurrentScene();
		if (themeChan != nullptr)
			themeChan->setPaused(false);
	}

	static ScriptDirection getNewScriptDirection(ScriptDirection direction, Hitbox hitbox, Hitbox firstHitbox, Hitbox lastHitbox)
	{
		if (direction == ScriptDirection::STILL)
		{
			if (hitbox.x1 > lastHitbox.x1)
				return (ScriptDirection::GOING_LEFT);
			if (hitbox.x1 < lastHitbox.x1)
				return (ScriptDirection::GOING_RIGHT);
			if (hitbox.y1 > lastHitbox.y1)
				return (ScriptDirection::GOING_BOTTOM);
			if (hitbox.y1 < lastHitbox.y1)
				return (ScriptDirection::GOING_TOP);
			if (hitbox.x1 == lastHitbox.x1 && hitbox.y1 == lastHitbox.y1
			&&	hitbox.x2 == lastHitbox.x2 && hitbox.y2 == lastHitbox.y2)
				return (ScriptDirection::STILL);
		}

		if (direction == ScriptDirection::GOING_LEFT
		&& ((lastHitbox.x1 > firstHitbox.x1	&& hitbox.x1 <= firstHitbox.x1)
		 || (lastHitbox.x1 < firstHitbox.x1 && hitbox.x1 <= lastHitbox.x1)))
			return (ScriptDirection::GOING_RIGHT);

		if (direction == ScriptDirection::GOING_RIGHT
		&& ((lastHitbox.x1 > firstHitbox.x1	&& hitbox.x1 >= lastHitbox.x1)
		 || (lastHitbox.x1 < firstHitbox.x1 && hitbox.x1 >= firstHitbox.x1)))
			return (ScriptDirection::GOING_LEFT);

		if (direction == ScriptDirection::GOING_BOTTOM
		&& ((lastHitbox.y1 > firstHitbox.y1	&& hitbox.y1 <= firstHitbox.y1)
		 || (lastHitbox.y1 < firstHitbox.y1 && hitbox.y1 <= lastHitbox.y1)))
			return (ScriptDirection::GOING_TOP);

		if (direction == ScriptDirection::GOING_TOP
		&& ((lastHitbox.y1 > firstHitbox.y1	&& hitbox.y1 >= lastHitbox.y1)
		 || (lastHitbox.y1 < firstHitbox.y1 && hitbox.y1 >= firstHitbox.y1)))
			return (ScriptDirection::GOING_BOTTOM);

		return (direction);
	}

	void	LevelScene::updateScriptsStatic()
	{
		for (auto staticEntity : _staticEntities)
			if (staticEntity->getIsScripted() == true)
			{
				ScriptDirection actualDirection = staticEntity->getScriptDirection();
				ScriptDirection newDirection = getNewScriptDirection(actualDirection,
																	 staticEntity->getHitbox(),
																	 staticEntity->getHitboxFirstPos(),
																	 staticEntity->getHitboxLastPos());

				if (actualDirection != newDirection)
					staticEntity->setScriptDirection(newDirection);

				if (newDirection == ScriptDirection::GOING_LEFT)
					staticEntity->getSprite()->move(Vector2f(-1, 0));
				else if (newDirection == ScriptDirection::GOING_RIGHT)
					staticEntity->getSprite()->move(Vector2f(1, 0));
				else if (newDirection == ScriptDirection::GOING_BOTTOM)
					staticEntity->getSprite()->move(Vector2f(0, -1));
				else if (newDirection == ScriptDirection::GOING_TOP)
					staticEntity->getSprite()->move(Vector2f(0, 1));
				staticEntity->resetHitbox();

				//std::cout << "y1: " << staticEntity->getHitbox().y1 << " && lastposY1:" << staticEntity->getHitboxLastPos().y1 << " && going ";
				//if (newDirection == ScriptDirection::GOING_LEFT)
				//	std::cout << "left";
				//else if (newDirection == ScriptDirection::GOING_RIGHT)
				//	std::cout << "right";
				//else if (newDirection == ScriptDirection::GOING_BOTTOM)
				//	std::cout << "bottom";
				//else if (newDirection == ScriptDirection::GOING_TOP)
				//	std::cout << "top";
				//else
				//	std::cout << "still";
				//std::cout << std::endl;
			}
	}

	Vector2f	LevelScene::updateScriptDynamic(std::shared_ptr<DynamicEntity> entity, Vector2f decal)
	{
		ScriptDirection actualDirection = entity->getScriptDirection();
		ScriptDirection newDirection = getNewScriptDirection(actualDirection,
															 entity->getHitbox(),
															 entity->getHitboxFirstPos(),
															 entity->getHitboxLastPos());

		if (actualDirection != newDirection)
			entity->setScriptDirection(newDirection);

		if (newDirection == ScriptDirection::GOING_LEFT)
		{
			decal.x -= 1;
			if (entity->getDirection() != Direction::LEFT)
				entity->setDirection(Direction::LEFT);
		}
		else if (newDirection == ScriptDirection::GOING_RIGHT)
		{
			decal.x += 1;
			if (entity->getDirection() != Direction::RIGHT)
				entity->setDirection(Direction::RIGHT);
		}
		else if (newDirection == ScriptDirection::GOING_BOTTOM)
			decal.y -= 1;
		else if (newDirection == ScriptDirection::GOING_TOP)
			decal.y += 1;
		else if (actualDirection == ScriptDirection::STILL)
			entity->setIsScripted(false);
		return (decal);
	}

	void	LevelScene::applyGravityAndCollisions()
	{
		//Init collison & gravity loop values
		HitZone hitZone;
		bool isInHeatZone;
		Vector2f decal(0, 0);

		//Deleting desactivated bullets
		clearEntityType(EntityType::BULLET, true);
		
		for (auto dynamicEntity : _dynamicEntities)
		{
			if (dynamicEntity->getIsActivated() == true
				&& (dynamicEntity->getEntityType() == EntityType::BULLET
					|| isVisible(*_player, *dynamicEntity.get(), 800)))
			{
				if (dynamicEntity->getIsScripted() == true)
					decal = updateScriptDynamic(dynamicEntity, Vector2f(0, 0));
				else
					decal = Vector2f(0, 0);

				if (dynamicEntity->getEntityType() == EntityType::PLAYER && _player->getHealth() > 1.f)
					_player->checkEvaporation();

				dynamicEntity->setGravity(true);

				if (dynamicEntity->getEntityType() == EntityType::BULLET)
				{
					if (dynamicEntity->getDirection() == Direction::RIGHT)
						dynamicEntity->setVelocity(Vector2f(STANDARD_VELOCITY_X * 2, dynamicEntity->getVelocity().y));
					else
						dynamicEntity->setVelocity(Vector2f(-STANDARD_VELOCITY_X * 2, dynamicEntity->getVelocity().y));
				}

				if (dynamicEntity->getGravity() == true)
				{
					(std::static_pointer_cast<Moo::Character>(dynamicEntity))->update();
					dynamicEntity->resetHitbox();
				}

				isInHeatZone = false;

				for (auto staticEntity : _staticEntities)
				{
					if (isVisible(*dynamicEntity.get(), *staticEntity.get(), 100) && staticEntity->isCollidable() == true
						&& (hitZone = dynamicEntity->collisionAABB(staticEntity.get())) != HitZone::NONE)
					{
						//If player collides with an Exit
						if (dynamicEntity->getEntityType() == EntityType::PLAYER && staticEntity->getEntityType() == EntityType::EXIT)
						{
							_exitReached = true;
							break;
						}
						//If player is in a heatzone
						else if (staticEntity->getEntityType() == EntityType::BLANK_HEAT_ZONE)
							isInHeatZone = true;
						//If we collide with a wall/platform/bottom
						else if (dynamicEntity->getEntityType() == EntityType::PLAYER || (dynamicEntity->getEntityType() == EntityType::ENEMY))
						{
							if (hitZone == HitZone::RIGHT_SIDE)
								decal.x = staticEntity->getHitbox().x1 - dynamicEntity->getHitbox().x2;
							else if (hitZone == HitZone::LEFT_SIDE)
								decal.x = staticEntity->getHitbox().x2 - dynamicEntity->getHitbox().x1;
							else if (hitZone == HitZone::TOP)
							{
								decal.y = staticEntity->getHitbox().y2 - dynamicEntity->getHitbox().y1;
								dynamicEntity->setVelocity(Vector2f(dynamicEntity->getVelocity().x, -1));
							}
							else if (hitZone == HitZone::BOTTOM)
							{
								decal.y = staticEntity->getHitbox().y1 - dynamicEntity->getHitbox().y2;
								dynamicEntity->resetPos();
								dynamicEntity->setGravity(false);
							}
						}
						else if (dynamicEntity->getEntityType() == EntityType::BULLET)
						{
							std::cout << "Deleting " << getEntityTypeName(dynamicEntity->getEntityType())
								<< " after its collision with " << getEntityTypeName(staticEntity->getEntityType()) << std::endl;
							dynamicEntity->setIsActivated(false);
							break;
						}
						if (isInHeatZone == false && staticEntity->getIsHeatZone() == true)
							isInHeatZone = true;
					}
				}

				if (dynamicEntity->getIsActivated() == false || _exitReached == true)
					break;
				
				if (decal.y != 0)
					dynamicEntity->getSprite()->setY(dynamicEntity->getSprite()->getY() + decal.y);
				if (decal.x != 0)
				{
					if (dynamicEntity->getEntityType() == EntityType::PLAYER)
						_canTemporarilyJump = std::chrono::system_clock::now();
					dynamicEntity->getSprite()->setX(dynamicEntity->getSprite()->getX() + decal.x);
				}

				dynamicEntity->resetHitbox();

				if (isInHeatZone == true
					&& (dynamicEntity->getEntityType() == EntityType::BULLET
						|| std::static_pointer_cast<Moo::Character>(dynamicEntity)->isGodMode() != true))
				{
					if (dynamicEntity->getHealth() < 0.5f || (dynamicEntity->getEntityType() == EntityType::BULLET && dynamicEntity->getHealth() < 0.975f))
					{
						std::cout << "Deleting " << getEntityTypeName(dynamicEntity->getEntityType()) << " because of heat zone evaporation" << std::endl;
						if (dynamicEntity->getEntityType() == EntityType::PLAYER)
							_playerDead = true;
						else
							dynamicEntity->setIsActivated(false);
						break;
					}
					dynamicEntity->evaporateHeatZone();
				}

				for (auto secondDynamicEntity : _dynamicEntities)
				{
					if (secondDynamicEntity->getIsActivated() == true
						&& isVisible(*dynamicEntity.get(), *secondDynamicEntity.get(), 200))
					{
						if (!(dynamicEntity->getEntityType() == EntityType::BULLET && secondDynamicEntity->getEntityType() == EntityType::BULLET)
							&& secondDynamicEntity.get() != dynamicEntity.get()
							&& ((hitZone = dynamicEntity->collisionAABB(secondDynamicEntity.get())) != HitZone::NONE))
						{
							//If we collide with an enemy : Absorb him
							//std::cout << "Collision between " << getEntityTypeName(dynamicEntity->getEntityType()) << " and " << getEntityTypeName(secondDynamicEntity->getEntityType()) << std::endl;
							if ((dynamicEntity->getEntityType() != EntityType::BULLET
								&& ((dynamicEntity->getHealth() <= secondDynamicEntity->getHealth()
								&& std::static_pointer_cast<Moo::Character>(dynamicEntity)->isGodMode() != true)
								|| (secondDynamicEntity->getEntityType() == EntityType::PLAYER && std::static_pointer_cast<Moo::Character>(secondDynamicEntity)->isGodMode() == true)))
								|| (dynamicEntity->getEntityType() == EntityType::BULLET && secondDynamicEntity->getEntityType() != EntityType::PLAYER))
							{
								_soundSystem->playSound("powerup", false);

								secondDynamicEntity->changeHealth(dynamicEntity->getHealth() * 33 / 100);

								if (dynamicEntity->getEntityType() != secondDynamicEntity->getEntityType())
								{
									std::cout << "Deleting " << getEntityTypeName(dynamicEntity->getEntityType())
										<< " after its collision with " << getEntityTypeName(secondDynamicEntity->getEntityType()) << std::endl;
									std::cout << getEntityTypeName(secondDynamicEntity->getEntityType()) << " health is now: " << secondDynamicEntity->getHealth() << std::endl;
								}

								if (dynamicEntity->getEntityType() == EntityType::PLAYER)
									_playerDead = true;
								dynamicEntity->setIsActivated(false);
								break;
							}
						}
					}
				}
			}
			if (_playerDead == true)
				break;
		}
		if (_exitReached == true)
			this->exitReached();
	}

	void	LevelScene::displayHudInfos()
	{
		_window->inCameradraw(_hud.get());

		_life.get()->setText(std::to_string(static_cast<int>(_player->getHealth())));
		_window->inCameradraw(_life.get());

		_fps->setText("FPS " + std::to_string(_window->getFps()));
		_window->inCameradraw(_fps.get());
	}

	bool	LevelScene::runUpdate()
	{
		////Gtting the inputs of the player
		//std::chrono::duration<double>	elapsed_time_start = std::chrono::system_clock::now() - _startTime;
		//if (elapsed_time_start.count() > 0.75)
		inputHandling();

		//Applying scripts
		updateScriptsStatic();

		//Applying gravity to dynamic entities and checking all collisions
		applyGravityAndCollisions();
		
		//Reseting the positon of the camera
		Moo::d3d::getInstance().getCamera()->update(_player->getHitbox());
		_camera = *Moo::d3d::getInstance().getCamera();

		//Display the game elements
		displayHitboxesAndSprites();

		//Display the HUD elements
		displayHudInfos();

		//Drawing all that is inside the window
		_window->display();

		if (_playerDead == true)
			this->playerDead();

		return true;
	}
}