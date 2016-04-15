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
		// clean 
	}

	void	LevelScene::getEntitiesFromMap(JsonParser *map)
	{
		Moo::Texture *characterText = new Moo::Texture;
		characterText->loadFromFile("character.dds");
		Moo::Texture *enemyText = new Moo::Texture;
		enemyText->loadFromFile("enemy.dds");
		Moo::Texture *platformText = new Moo::Texture;
		platformText->loadFromFile("platform.dds");
		Moo::Texture *groundText = new Moo::Texture;
		groundText->loadFromFile("ground.dds");
		Moo::Texture *blocText = new Moo::Texture;
		blocText->loadFromFile("bloc.dds");
		Moo::Texture *exitText = new Moo::Texture;
		exitText->loadFromFile("door_closed.dds");

		//All the data contained in the map
		std::list<Tile *> playerTiles = map->getMap().getTilesFromColor("#ffabcdef"); //blue
		std::list<Tile *> platformTiles = map->getMap().getTilesFromColor("#fff93738"); //red
		std::list<Tile *> bottomTiles = map->getMap().getTilesFromColor("#ff117050"); //green
		std::list<Tile *> enemyTiles = map->getMap().getTilesFromColor("#ff000000"); //black
		std::list<Tile *> blocTiles = map->getMap().getTilesFromColor("#ff551A8B"); //purple
		std::list<Tile *> exitTiles = map->getMap().getTilesFromColor("#ffffd700"); //gold

		//Because the map created by the map editor are not in WINDOW_HEIGHT * WINDOW_WIDTH resolution
		/*float multHeight = WINDOW_HEIGHT / map->getMap().getMapHeight();
		float multWidth = WINDOW_WIDTH / map->getMap().getMapWidth();

		std::cout << "multHeight: " << multHeight << std::endl;
		std::cout << "multWidth: " << multWidth << std::endl;*/

		//counter
		int i = 1;

		//Player specs
		float playerHeight = 48.4;
		float playerWidth = 48.4;
		float playerMass = 300;

		//Enemies specs
		float enemiesHeight = 40;
		float enemiesWidth = 40;
		float enemiesMass = 100;

		//Enemies
		for (std::list<Tile *>::const_iterator it = enemyTiles.begin(); it != enemyTiles.end(); ++it)
		{
			Moo::Sprite *enemySprite = new Moo::Sprite(enemiesWidth, enemiesHeight, (*it)->getPosX() * 40, (*it)->getPosY() * 40);
			enemySprite->loadTexture(enemyText);
			Moo::Character *enemy = new Moo::Character(Moo::Vector2f(1, 0), enemiesMass, enemySprite, true, 4);
			enemy->setCollision(true);
			// To make sure that enemies have less health than us at the beginning
			enemy->setHealth(4);
			enemySprite->scale(Moo::Vector2f(-0.1f, -0.1f));
			enemy->getHitboxSprite()->setScale(enemy->getSprite()->getScale());
			dynamicEntities.push_back(std::make_pair("Enemy " + std::to_string(i), enemy));
			++i;
		}

		//reset counter
		i = 1;

		//platforms
		for (std::list<Tile *>::const_iterator it = platformTiles.begin(); it != platformTiles.end(); ++it)
		{
			Moo::Sprite *platform = new Moo::Sprite(40, 40, (*it)->getPosX() * 40, (*it)->getPosY() * 40);
			platform->loadTexture(platformText);
			Moo::Character *platformEntity = new Moo::Character(Moo::Vector2f(1, 0), 0, platform, false, 0);
			staticEntities.push_back(std::make_pair("Platform " + std::to_string(i), platformEntity));
			++i;
		}

		//bloc
		for (std::list<Tile *>::const_iterator it = blocTiles.begin(); it != blocTiles.end(); ++it)
		{
			Moo::Sprite *bloc = new Moo::Sprite(40, 40, (*it)->getPosX() * 40, (*it)->getPosY() * 40);
			bloc->loadTexture(blocText);
			staticEntities.push_back(std::make_pair("Bloc", new Moo::Character(Moo::Vector2f(1, 0), 0, bloc, false, 0)));
		}

		//bottom
		for (std::list<Tile *>::const_iterator it = bottomTiles.begin(); it != bottomTiles.end(); ++it)
		{
			Moo::Sprite *ground = new Moo::Sprite(40, 40, (*it)->getPosX() * 40, (*it)->getPosY() * 40);
			ground->loadTexture(groundText);
			staticEntities.push_back(std::make_pair("Bottom", new Moo::Character(Moo::Vector2f(1, 0), 0, ground, false, 0)));
		}

		//exit
		for (std::list<Tile *>::const_iterator it = exitTiles.begin(); it != exitTiles.end(); ++it)
		{
			Moo::Sprite *exit = new Moo::Sprite(40, 40, (*it)->getPosX() * 40, (*it)->getPosY() * 40);
			exit->loadTexture(exitText);
			Moo::Character *exitEntity = new Moo::Character(Moo::Vector2f(1, 0), 0, exit, false, 0);
			staticEntities.push_back(std::make_pair("Exit " + std::to_string(i), exitEntity));
			++i;
		}

		if (playerTiles.size() > 0)
		{
			//Get the first element because there is only one player
			std::list<Tile *>::const_iterator playerIt = playerTiles.begin();

			//Player
			Moo::Sprite *character = new Moo::Sprite(playerWidth, playerHeight, (*playerIt)->getPosX() * 40, (*playerIt)->getPosY() * 40);
			character->loadTexture(characterText);
			Moo::Character *player = new Moo::Character(Moo::Vector2f(0, 0), playerMass, character, true, 6);
			//The player is always the first of the entities vector
			dynamicEntities.insert(dynamicEntities.begin(), std::make_pair("Player", player));
		}

		// release Textures
		//marioText->release();
		//platformText->release();
		//groundText->~Texture();
	}

	Camera LevelScene::getCamera()
	{
		return _camera;
	}

	bool	LevelScene::init(std::shared_ptr<Window> window)
	{
		_window = window;

		backgroundText = new Moo::Texture;
		backgroundText->loadFromFile("background.dds");

		//We get the map
		//map = new JsonParser("2d-Maps/50x50.json");
		map = new JsonParser("2d-Maps/MapPreAlpha.json");

		if (map->parseFile() == -1)
			throw std::exception("Can't load the map");

		//map->getMap().displayMapInfos();

		//Read the entities from the map
		getEntitiesFromMap(map);

		//background
		background = new Moo::Sprite(4000, 3000, 0, 0);
		background->loadTexture(backgroundText);

		player = dynamic_cast<Moo::Character *>(dynamicEntities[0].second);

		// Temp texture for the bullet
		bulletText = new Moo::Texture;
		bulletText->loadFromFile("character.dds");
		loseText = new Moo::Texture;
		loseText->loadFromFile("You_Lost_DDS.dds");
		winText = new Moo::Texture;
		winText->loadFromFile("You_Won_DDS.dds");
		Moo::d3d::getInstance().getCamera()->setInfoMap(map->getMap());

		lose = new Moo::Sprite(400, 133, 0, 0);
		lose->loadTexture(loseText);
		win = new Moo::Sprite(400, 133,	0, 0);
		win->loadTexture(winText);

		//init sound system
		_soundSystem = Game::getInstance().getSoundSystem();

		if (_soundSystem->addSound(map->getMap().getMapAudioFile().c_str(), "custom"))
		{
			std::cout << map->getMap().getMapAudioFile() << std::endl;
			std::cout << "music failed" << std::endl;
			themeChan = nullptr;
		}

		themeChan = _soundSystem->playSound("custom", true);
		if (themeChan != nullptr)
			themeChan->setPaused(true);

		player->setTimers();
		_startTime = std::chrono::system_clock::now();
		_canTemporarilyJump = _startTime;

		return (true);
	}

	void	LevelScene::inputHandling()
	{
		//Reseting _triedJump to check if the player tries to wall jump this frame
		_triedJump = false;

		if (Moo::Keyboard::isPressed(Moo::Keyboard::A))
		{
			if (themeChan != nullptr)
				themeChan->setPaused(true);
			_camera.setPosition(d3d::getInstance().getCamera()->getPosition());
			Moo::Game::getInstance().runScene(Game::PAUSE_MENU);
		}

		if (Moo::Keyboard::isPressed(Moo::Keyboard::B))
			if (themeChan != nullptr)
				themeChan->setPaused(false);

		if (Moo::Keyboard::isPressed(Moo::Keyboard::C))
			if (themeChan != nullptr)
				themeChan->setPaused(true);

		//Cheats
		if (Moo::Keyboard::isDown(Moo::Keyboard::GodMode))
			player->toggleGodMode();

		if (Moo::Keyboard::isDown(Moo::Keyboard::SizeUp))
			player->changeHealth(1);

		if (Moo::Keyboard::isDown(Moo::Keyboard::SizeDown))
			player->changeHealth(-1);

		if (Moo::Keyboard::isDown(Moo::Keyboard::Space))
		{
			bool wallJump = false;
			if (player->getVelocity().y > 0)
			{
				std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - _canTemporarilyJump;
				if (elapsed_seconds.count() < 0.1)
				{
					std::cout << "The player tried to jump" << std::endl;
					wallJump = true;
					if (player->getVelocity().x < 0)
						player->setVelocity(Vector2f(STANDARD_VELOCITY_X * 2, player->getVelocity().y));
					else
						player->setVelocity(Vector2f(-STANDARD_VELOCITY_X * 2, player->getVelocity().y));
				}
				else
					std::cout << "Too late to wall jump, elapsed seconds count: " << elapsed_seconds.count() << std::endl;
			}
			if (player->jump(wallJump) == true)
				_canTemporarilyJump = _startTime;
		}

		if (Moo::Keyboard::isPressed(Moo::Keyboard::Left))
			player->move(Direction::LEFT);

		if (Moo::Keyboard::isPressed(Moo::Keyboard::Right))
			player->move(Direction::RIGHT);

		if (Moo::Keyboard::isDown(Moo::Keyboard::Shot))
		{
			if (player->getHealth() > 1)
			{
				_soundSystem->playSound("jump", false);
				// Define the base pos of the bullet and create the sprite
				float bulletPosX = player->getSprite()->getX() + (player->getSprite()->getWidth());
				float bulletPosY = player->getSprite()->getY() + (player->getSprite()->getHeight() / 2);
				Moo::Sprite *bulletSprite = new Moo::Sprite(5, 5, bulletPosX, bulletPosY);

				bulletSprite->loadTexture(bulletText);

				// Creation of the bullet
				Moo::Bullet *bullet = new Moo::Bullet(bulletSprite, false);
				bullet->setCollision(true);

				// Addition of the bullet to the bullet pool
				dynamicEntities.push_back(std::pair<std::string, Moo::Entity *>("bullet", bullet));

				// Check if cheat code is activated.
				if (player->isGodMode() == false)
					player->changeHealth(-0.3);
				std::cout << "Player health : " << player->getHealth() << std::endl;
			}
			else
				std::cout << "Player is too small to shoot" << std::endl;
		}
	}

	void	LevelScene::displayHitboxesAndSprites()
	{
		_window->clear();
		_window->draw(background);

		// Display hitbox if godmode is on
		if (player->isGodMode() == true)
			_window->draw(player->getHitboxSprite());

		//Draw static entities and their hitboxes
		for (unsigned int i = 0; i < staticEntities.size(); ++i)
		{
			_window->draw(((Moo::Character *)staticEntities[i].second)->getSprite());
			_window->draw(((Moo::Character *)staticEntities[i].second)->getHitboxSprite());
		}

		//Draw dynamic entities and their hitboxes
		for (unsigned int i = 0; i < dynamicEntities.size(); ++i)
		{
			_window->draw(((Moo::Character *)dynamicEntities[i].second)->getSprite());
			_window->draw(((Moo::Character *)dynamicEntities[i].second)->getHitboxSprite());
			if (_strnicmp(dynamicEntities[i].first.c_str(), "Enemy", 5) == 0)
				((Moo::Character *)dynamicEntities[i].second)->getSprite()->rotate(1);
		}
	}

	void	LevelScene::exitReached()
	{
		win->setPosition(((Moo::d3d::getInstance().getCamera()->getPosition().x * -1) +
						  (Moo::d3d::getInstance().getScreenSize().x / 2 - 200)),
						 ((Moo::d3d::getInstance().getCamera()->getPosition().y * -1) +
						  (Moo::d3d::getInstance().getScreenSize().y / 2))
			);
		if (themeChan != nullptr)
			themeChan->setPaused(true);
		FMOD::Channel *chan = _soundSystem->playSound("victory", false);
		_window->draw(win);
		_window->display();
		Sleep(1000);
		chan->stop();
		Game::getInstance().runScene(Game::MAIN_MENU);
	}

	void	LevelScene::playerDead()
	{
		lose->setPosition(((Moo::d3d::getInstance().getCamera()->getPosition().x * -1) +
						   (Moo::d3d::getInstance().getScreenSize().x / 2 - 250)),
						  ((Moo::d3d::getInstance().getCamera()->getPosition().y * -1) +
						   (Moo::d3d::getInstance().getScreenSize().y / 2))
			);
		if (themeChan != nullptr)
			themeChan->setPaused(true);
		FMOD::Channel *chan = _soundSystem->playSound("defeat", false);
		_window->draw(lose);
		_window->display();
		Sleep(1000);
		chan->stop();
		Game::getInstance().runScene(Game::MAIN_MENU);
	}

	void	LevelScene::applyGravityAndCollisions()
	{
		//Init collison & gravity loop values
		HitZone hitZone;
		bool deletedBullet;
		bool deletedCharacter;
		bool isPlayer;
		Vector2f decal(0, 0);

		for (std::vector<std::pair<std::string, Moo::Entity *>>::iterator dynEntIt = dynamicEntities.begin(); dynEntIt != dynamicEntities.end();)
		{
			decal = Vector2f(0, 0);
			if ((*dynEntIt).second == player)
			{
				isPlayer = true;
				if (player->getHealth() > 1)
					player->checkEvaporation();
			}
			else
				isPlayer = false;
			(*dynEntIt).second->setGravity(true);
			if ((*dynEntIt).second->getGravity() == true)
			{
				((Moo::Character *)(*dynEntIt).second)->update();
				((Moo::Character *)(*dynEntIt).second)->resetHitbox();
			}
			deletedBullet = false;
			deletedCharacter = false;

			if (_strnicmp((*dynEntIt).first.c_str(), "Bullet", 6) == 0)
				(*dynEntIt).second->setVelocity(Vector2f(STANDARD_VELOCITY_X * 2, (*dynEntIt).second->getVelocity().y));

			for (std::vector<std::pair<std::string, Moo::Entity *>>::iterator statEntIt = staticEntities.begin();
				 statEntIt != staticEntities.end();
				 ++statEntIt)
			{
				if ((hitZone = (*dynEntIt).second->collisionAABB((*statEntIt).second)) != HitZone::NONE)
				{
					//If player collides with an Exit
					if (isPlayer == true && _strnicmp((*statEntIt).first.c_str(), "Exit", 4) == 0)
						exitReached();
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
							((Moo::Character *)(*dynEntIt).second)->resetPos();
							(*dynEntIt).second->setGravity(false);
						}
					}
					else if (_strnicmp((*dynEntIt).first.c_str(), "Bullet", 6) == 0)
					{
						std::cout << "Deleting " << (*dynEntIt).first << std::endl;
						delete (*dynEntIt).second;
						dynEntIt = dynamicEntities.erase(dynEntIt);
						deletedBullet = true;
						break;
					}
				}
			}

			if (deletedBullet == false)
			{
				Moo::Character *character = ((Moo::Character *)(*dynEntIt).second);
				if (decal.y != 0)
					character->getSprite()->setY(character->getSprite()->getY() + decal.y);
				if (decal.x != 0)
				{
					_canTemporarilyJump = std::chrono::system_clock::now();
					character->getSprite()->setX(character->getSprite()->getX() + decal.x);
				}
				character->resetHitbox();

				for (std::vector<std::pair<std::string, Moo::Entity *>>::iterator SecondDynEntIt = dynamicEntities.begin();
					 SecondDynEntIt != dynamicEntities.end();
					 ++SecondDynEntIt)
				{
					if ((*SecondDynEntIt).second != character
					 && ((hitZone = character->collisionAABB((*SecondDynEntIt).second)) != HitZone::NONE))
					{
						//If we collide with an enemy : Absorb him
						std::cout << "Collision between " << (*dynEntIt).first << " and " << (*SecondDynEntIt).first << std::endl;
						if (_strnicmp((*SecondDynEntIt).first.c_str(), "Enemy", 5) == 0)
						{
							Moo::Character *enemyCollided = ((Moo::Character *)(*SecondDynEntIt).second);
							if (_strnicmp((*dynEntIt).first.c_str(), "Bullet", 6) == 0)
							{
								delete character;
								dynEntIt = dynamicEntities.erase(dynEntIt);
								deletedBullet = true;
								enemyCollided->changeHealth(0.3);
								std::cout << (*SecondDynEntIt).first << " health: " << enemyCollided->getHealth() << std::endl;
								break;
							}
							else 
							{
								if (character->getHealth() >= enemyCollided->getHealth() || character->isGodMode() == true)
								{
									character->changeHealth(enemyCollided->getHealth() * 33 / 100);
									std::cout << (*dynEntIt).first << " health: " << character->getHealth() << std::endl;
									SecondDynEntIt = dynamicEntities.erase(SecondDynEntIt);
									deletedCharacter = true;
									break;
								}
								else if (isPlayer == true)
									playerDead();
								else
								{
									enemyCollided->changeHealth(character->getHealth() * 33 / 100);
									std::cout << (*SecondDynEntIt).first << " health: " << enemyCollided->getHealth() << std::endl;
									dynEntIt = dynamicEntities.erase(dynEntIt);
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
			else if (deletedCharacter == true)
				break;
		}
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
		Moo::d3d::getInstance().getCamera()->update(player->getHitbox());

		//Display the game elements
		displayHitboxesAndSprites();

		//Drawing all that is inside the window
		_window->display();


		/*
		if (themeChan != nullptr)
			themeChan->setPaused(true);
		*/
		return (false);
	}
}