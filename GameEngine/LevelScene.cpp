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
		float playerHeight = 40;
		float playerWidth = 40;
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
			Moo::Character *enemy = new Moo::Character(Moo::Vector2f(1, 0), enemiesMass, enemySprite, true);
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
			Moo::Character *platformEntity = new Moo::Character(Moo::Vector2f(1, 0), 0, platform, false);
			staticEntities.push_back(std::make_pair("Platform " + std::to_string(i), platformEntity));
			++i;
		}

		//bloc
		for (std::list<Tile *>::const_iterator it = blocTiles.begin(); it != blocTiles.end(); ++it)
		{
			Moo::Sprite *bloc = new Moo::Sprite(40, 40, (*it)->getPosX() * 40, (*it)->getPosY() * 40);
			bloc->loadTexture(blocText);
			staticEntities.push_back(std::make_pair("Bloc", new Moo::Character(Moo::Vector2f(1, 0), 0, bloc, false)));
		}

		//bottom
		for (std::list<Tile *>::const_iterator it = bottomTiles.begin(); it != bottomTiles.end(); ++it)
		{
			Moo::Sprite *ground = new Moo::Sprite(40, 40, (*it)->getPosX() * 40, (*it)->getPosY() * 40);
			ground->loadTexture(groundText);
			staticEntities.push_back(std::make_pair("Bottom", new Moo::Character(Moo::Vector2f(1, 0), 0, ground, false)));
		}

		//exit
		for (std::list<Tile *>::const_iterator it = exitTiles.begin(); it != exitTiles.end(); ++it)
		{
			Moo::Sprite *exit = new Moo::Sprite(40, 40, (*it)->getPosX() * 40, (*it)->getPosY() * 40);
			exit->loadTexture(exitText);
			Moo::Character *exitEntity = new Moo::Character(Moo::Vector2f(1, 0), 0, exit, false);
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
			Moo::Character *player = new Moo::Character(Moo::Vector2f(STANDARD_VELOCITY_X, 0), playerMass, character, true);
			//The player is always the first of the entities vector
			dynamicEntities.insert(dynamicEntities.begin(), std::make_pair("Player", player));
		}

		// release Textures
		//marioText->release();
		//platformText->release();
		//groundText->~Texture();
	}

	bool	LevelScene::init()
	{
		if (!jump.loadSound("jump.wav")) {
			std::cout << "jump sound failed" << std::endl;
		}
		if (!soundWin.loadSound("Victory.wav")) {
			std::cout << "win sound failed" << std::endl;
		}		
		if (!soundLose.loadSound("Defeat.wav")) {
			std::cout << "lose sound failed" << std::endl;
		}
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

		if (!music.loadSound(map->getMap().getMapAudioFile()))
		{
			std::cout << map->getMap().getMapAudioFile() << std::endl;
			std::cout << "music failed" << std::endl;
		}

		//background
		background = new Moo::Sprite(4000, 3000, 0, 0);
		background->loadTexture(backgroundText);

		player = dynamic_cast<Moo::Character *>(dynamicEntities[0].second);

		// Temp texture for the bullet
		bulletText = new Moo::Texture;
		bulletText->loadFromFile("platform.dds");
		loseText = new Moo::Texture;
		loseText->loadFromFile("You_Lost_DDS.dds");
		winText = new Moo::Texture;
		winText->loadFromFile("You_Won_DDS.dds");
		Moo::d3d::getInstance().getCamera()->setInfoMap(map->getMap());

		lose = new Moo::Sprite(400, 133, 0, 0);
		lose->loadTexture(loseText);
		win = new Moo::Sprite(400, 133,	0, 0);
		win->loadTexture(winText);

		return (true);
	}

	bool	LevelScene::inputHandling(Moo::Window &window)
	{
		if (Moo::Keyboard::isPressed(Moo::Keyboard::A))
		{
			audio.pauseSound(music);
			camera.setPosition(d3d::getInstance().getCamera()->getPosition());
			Moo::Game::getInstance().runScene(TypeScene::PAUSE, TypeScene::LEVEL, window);
			return (true);
		}

		if (Moo::Keyboard::isPressed(Moo::Keyboard::B))
			audio.playSound(music, true);

		if (Moo::Keyboard::isPressed(Moo::Keyboard::C))
			audio.pauseSound(music);

		//Cheats
		if (Moo::Keyboard::isDown(Moo::Keyboard::GodMode))
			player->toggleGodMode();

		if (Moo::Keyboard::isDown(Moo::Keyboard::SizeUp))
		{
			player->setHealth(player->getHealth() + 1);
			player->getSprite()->scale(Moo::Vector2f(0.1f, 0.1f));
			player->getHitboxSprite()->setScale(player->getSprite()->getScale());
		}

		if (Moo::Keyboard::isDown(Moo::Keyboard::SizeDown))
		{
			player->setHealth(player->getHealth() - 1);
			player->getSprite()->scale(Moo::Vector2f(-0.1f, -0.1f));
			player->getHitboxSprite()->setScale(player->getSprite()->getScale());
		}

		if (Moo::Keyboard::isDown(Moo::Keyboard::Space))
			 _triedJump = player->jump(false);

		if (Moo::Keyboard::isPressed(Moo::Keyboard::Left))
			player->move(Direction::LEFT);

		if (Moo::Keyboard::isPressed(Moo::Keyboard::Right))
			player->move(Direction::RIGHT);

		if (Moo::Keyboard::isDown(Moo::Keyboard::Shot))
		{
			if (player->getHealth() > 1)
			{
				audio.playSound(jump, false);

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
				{
					int currentHealth = player->getHealth();
					player->setHealth(currentHealth - 1);
					player->getSprite()->scale(Moo::Vector2f(-0.1f, -0.1f));
					player->getHitboxSprite()->setScale(player->getSprite()->getScale());
				}
				std::cout << "Player health : " << player->getHealth() << std::endl;
			}
			else
				std::cout << "Player is too small to shoot" << std::endl;
		}
		return (false);
	}

	void	LevelScene::displayHitboxesAndSprites(Moo::Window &window)
	{
		window.clear();
		window.draw(background);

		// Display hitbox if godmode is on
		if (player->isGodMode() == true)
			window.draw(player->getHitboxSprite());

		//Draw static entities and their hitboxes
		for (unsigned int i = 0; i < staticEntities.size(); ++i)
		{
			window.draw(((Moo::Character *)staticEntities[i].second)->getSprite());
			window.draw(((Moo::Character *)staticEntities[i].second)->getHitboxSprite());
		}

		//Draw dynamic entities and their hitboxes
		for (unsigned int i = 0; i < dynamicEntities.size(); ++i)
		{
			window.draw(((Moo::Character *)dynamicEntities[i].second)->getSprite());
			window.draw(((Moo::Character *)dynamicEntities[i].second)->getHitboxSprite());
			if (_strnicmp(dynamicEntities[i].first.c_str(), "Enemy", 5) == 0)
				((Moo::Character *)dynamicEntities[i].second)->getSprite()->rotate(1);
		}
	}

	void	LevelScene::exitReached(Moo::Window &window)
	{
		win->setPosition(((Moo::d3d::getInstance().getCamera()->getPosition().x * -1) +
						  (Moo::d3d::getInstance().getScreenSize().x / 2 - 200)),
						 ((Moo::d3d::getInstance().getCamera()->getPosition().y * -1) +
						  (Moo::d3d::getInstance().getScreenSize().y / 2))
			);
		audio.pauseSound(music);
		audio.playSound(soundWin, false);
		window.draw(win);
		window.display();
		Sleep(1000);
		audio.pauseSound(soundWin);
		Game::getInstance().runScene(TypeScene::MENU, TypeScene::LEVEL, window);
	}

	void	LevelScene::playerDead(Moo::Window &window)
	{
		lose->setPosition(((Moo::d3d::getInstance().getCamera()->getPosition().x * -1) +
						   (Moo::d3d::getInstance().getScreenSize().x / 2 - 250)),
						  ((Moo::d3d::getInstance().getCamera()->getPosition().y * -1) +
						   (Moo::d3d::getInstance().getScreenSize().y / 2))
			);
		audio.pauseSound(music);
		audio.playSound(soundLose, false);
		window.draw(lose);
		window.display();
		Sleep(1000);
		audio.pauseSound(soundLose);
		Game::getInstance().runScene(TypeScene::MENU, TypeScene::LEVEL, window);
	}

	bool	LevelScene::applyGravityAndCollisions(Moo::Window &window)
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
				isPlayer = true;
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
				decal.x = STANDARD_VELOCITY_X;

			for (std::vector<std::pair<std::string, Moo::Entity *>>::iterator statEntIt = staticEntities.begin();
				 statEntIt != staticEntities.end();
				 ++statEntIt)
			{
				if ((hitZone = (*dynEntIt).second->collisionAABB((*statEntIt).second)) != HitZone::NONE)
				{
					//If player collides with an Exit
					if (isPlayer == true && _strnicmp((*statEntIt).first.c_str(), "Exit", 4) == 0)
					{
						exitReached(window);
						return false;
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
				{/*
					if (isPlayer == true && _triedJump == true && player->getVelocity().y > 0)
					{
						std::cout << "The player tried to jump" << std::endl;
						player->jump(true);
						if (decal.x > 0)
							decal.x += 25;
						else
							decal.x -= 25;
					}*/
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
						//std::cout << (*dynEntIt).first << " x1: " << (*dynEntIt).second->getHitbox().x1 << " y1: " << (*dynEntIt).second->getHitbox().y1
						//		  << " x2: " << (*dynEntIt).second->getHitbox().x2 << " y2: " << (*dynEntIt).second->getHitbox().y2 << std::endl
						//		  << (*SecondDynEntIt).first << " x1: " << (*SecondDynEntIt).second->getHitbox().x1 << " y1: " << (*SecondDynEntIt).second->getHitbox().y1
						//		  << " x2: " << (*SecondDynEntIt).second->getHitbox().x2 << " y2: " << (*SecondDynEntIt).second->getHitbox().y2 << std::endl;
						//If we collide with an enemy : Absorb him
						if (_strnicmp((*SecondDynEntIt).first.c_str(), "Enemy", 5) == 0)
						{
							Moo::Character *enemyCollided = ((Moo::Character *)(*SecondDynEntIt).second);
							if (_strnicmp((*dynEntIt).first.c_str(), "Bullet", 6) == 0)
							{
								delete character;
								dynEntIt = dynamicEntities.erase(dynEntIt);
								deletedBullet = true;
								enemyCollided->setHealth(enemyCollided->getHealth() + 1);
								enemyCollided->getSprite()->scale(Moo::Vector2f(0.1f, 0.1f));
								enemyCollided->getHitboxSprite()->setScale(enemyCollided->getSprite()->getScale());
								enemyCollided->resetHitbox();
								std::cout << (*SecondDynEntIt).first << " health: " << enemyCollided->getHealth() << std::endl;
								break;
							}
							else 
							{
								if (character->getHealth() >= enemyCollided->getHealth() || character->isGodMode() == true)
								{
									//std::cout << "Bigger - Deleting " << (*SecondDynEntIt).first << std::endl;
									character->setHealth(character->getHealth() + (enemyCollided->getHealth() * 33 / 100));
									character->getSprite()->scale(Moo::Vector2f(0.1f * (enemyCollided->getHealth() * 33 / 100),
																				0.1f * (enemyCollided->getHealth() * 33 / 100)));
									character->getHitboxSprite()->setScale(character->getSprite()->getScale());
									character->resetHitbox();
									std::cout << (*dynEntIt).first << " health: " << character->getHealth() << std::endl;
									SecondDynEntIt = dynamicEntities.erase(SecondDynEntIt);
									deletedCharacter = true;
									break;
								}
								else if (isPlayer == true)
								{
									playerDead(window);
									return (false);
								}
								else
								{
									//std::cout << "Smaller - Deleting " << (*dynEntIt).first << std::endl;
									enemyCollided->setHealth(enemyCollided->getHealth() + (character->getHealth() * 33 / 100));
									enemyCollided->getSprite()->scale(Moo::Vector2f(0.1f * (character->getHealth() * 33 / 100),
																					0.1f * (character->getHealth() * 33 / 100)));
									enemyCollided->getHitboxSprite()->setScale(enemyCollided->getSprite()->getScale());
									enemyCollided->resetHitbox();
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
			{
				//std::cout << "A dynamic entity is deleted so we break" << std::endl;
				break;
			}
		}
		return (true);
	}

	bool	LevelScene::run(Moo::Window &window)
	{
		d3d::getInstance().getCamera()->setPosition(camera.getPosition());
		audio.playSound(music, true);

		while (window.isOpen())
		{
			//Reseting _triedJump to check if the player tries to wall jump this frame
			_triedJump = false;

			//Getting the inputs of the player
			if (inputHandling(window) == true)
				return (true);

			//Applying gravity to dynamic entities and checking all collisions
			if (applyGravityAndCollisions(window) == false)
				return (false);

			//Reseting the positon of the camera
			Moo::d3d::getInstance().getCamera()->update(player->getHitbox());

			//Display the game elements
			displayHitboxesAndSprites(window);

			//Drawing all that is inside the window
			window.display();
		}
		audio.pauseSound(music);
		//backgroundText->release();

		return (false);
	}
}