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

	std::vector<std::pair<std::string, Moo::Entity *>>	LevelScene::getEntitiesFromMap(JsonParser *map)
	{
		//List of entities of the game
		std::vector<std::pair<std::string, Moo::Entity *>> entities;

		Moo::Texture *marioText = new Moo::Texture;
		marioText->loadFromFile("mario.dds");
		Moo::Texture *platformText = new Moo::Texture;
		platformText->loadFromFile("platform.dds");
		Moo::Texture *groundText = new Moo::Texture;
		groundText->loadFromFile("ground.dds");

		//All the data contained in the map
		std::list<Tile *> playerTiles = map->getMap().getTilesFromColor("#ffabcdef"); //blue
		std::list<Tile *> platformTiles = map->getMap().getTilesFromColor("#fff93738"); //red
		std::list<Tile *> bottomTiles = map->getMap().getTilesFromColor("#ff117050"); //green
		std::list<Tile *> enemyTiles = map->getMap().getTilesFromColor("#ff000000"); //black
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
			enemySprite->loadTexture(marioText);
			Moo::Character *enemy = new Moo::Character(Moo::Vector2f(1, 0), enemiesMass, enemySprite, false);
			enemy->setCollision(true);
			// To make sure that enemies have less health than us at the beginning
			enemy->setHealth(4);
			enemySprite->scale(Moo::Vector2f(-0.1f, -0.1f));
			enemy->getHitboxSprite()->setScale(enemy->getSprite()->getScale());
			entities.push_back(std::make_pair("Enemy " + std::to_string(i), enemy));
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
			entities.push_back(std::make_pair("Platform " + std::to_string(i), platformEntity));
			++i;
		}

		//bottom
		for (std::list<Tile *>::const_iterator it = bottomTiles.begin(); it != bottomTiles.end(); ++it)
		{
			Moo::Sprite *ground = new Moo::Sprite(40, 40, (*it)->getPosX() * 40, (*it)->getPosY() * 40);
			ground->loadTexture(groundText);
			entities.push_back(std::make_pair("Bottom", new Moo::Character(Moo::Vector2f(1, 0), 0, ground, false)));
		}

		//exit
		for (std::list<Tile *>::const_iterator it = exitTiles.begin(); it != exitTiles.end(); ++it)
		{
			Moo::Sprite *exit = new Moo::Sprite(40, 40, (*it)->getPosX() * 40, (*it)->getPosY() * 40);
			exit->loadTexture(platformText);
			Moo::Character *exitEntity = new Moo::Character(Moo::Vector2f(1, 0), 0, exit, false);
			entities.push_back(std::make_pair("Exit " + std::to_string(i), exitEntity));
			++i;
		}

		if (playerTiles.size() > 0)
		{
			//Get the first element because there is only one player
			std::list<Tile *>::const_iterator playerIt = playerTiles.begin();

			//Player
			Moo::Sprite *mario = new Moo::Sprite(playerWidth, playerHeight, (*playerIt)->getPosX() * 40, (*playerIt)->getPosY() * 40);
			mario->loadTexture(marioText);
			Moo::Character *player = new Moo::Character(Moo::Vector2f(5, 0), playerMass, mario, true);
			//The player is always the first of the entities vector
			entities.insert(entities.begin(), std::make_pair("Player", player));
		}

		// release Textures
		//marioText->release();
		//platformText->release();
		//groundText->~Texture();

		return (entities);
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

		try
		{
			//We get the map
			map = new JsonParser("2d-Maps/50x50.json");

			if (map->parseFile() == -1)
				throw std::string("Can't load the map");
			//map->getMap().displayMapInfos();

			if (!music.loadSound(map->getMap().getMapAudioFile())) {
				std::cout << map->getMap().getMapAudioFile() << std::endl;
				std::cout << "music failed" << std::endl;
			}

			//Read the entities from the map
			entities = getEntitiesFromMap(map);
		}
		catch (std::string error)
		{
			std::cout << "Error: " << error << std::endl;
		}

		//background
		background = new Moo::Sprite(4000, 3000, 0, 0);
		background->loadTexture(backgroundText);

		player = dynamic_cast<Moo::Character *>(entities[0].second);

		// Temp texture for the bullet
		bulletText = new Moo::Texture;
		bulletText->loadFromFile("platform.dds");
		loseText = new Moo::Texture;
		loseText->loadFromFile("You_Lost_DDS.dds");
		winText = new Moo::Texture;
		winText->loadFromFile("You_Won_DDS.dds");

		return true;
	}

	bool	LevelScene::run(Moo::Window &window)
	{
		d3d::getInstance().getCamera()->setPosition(camera.getPosition());
		audio.playSound(music, true);
		while (window.isOpen())
		{
			//Sam DEbug

			//std::cout << "camera x = " << Moo::d3d::getInstance().getCamera()->getPosition().x << std::endl;
			//std::cout << "camera y = " << Moo::d3d::getInstance().getCamera()->getPosition().y << std::endl;
			//std::cout << "player x = " << player->getHitbox().x1 << std::endl;
			//std::cout << "player y = " << player->getHitbox().y1 << std::endl;

			if (Moo::Keyboard::isPressed(Moo::Keyboard::A)) {
				audio.pauseSound(music);
				camera.setPosition(d3d::getInstance().getCamera()->getPosition());
				Moo::Game::getInstance().runScene(TypeScene::PAUSE, TypeScene::LEVEL, window);
				return true;
			}
			if (Moo::Keyboard::isPressed(Moo::Keyboard::B)) {
				audio.playSound(music, true);
			}
			if (Moo::Keyboard::isPressed(Moo::Keyboard::C)) {
				audio.pauseSound(music);
			}

			//Cheats
			if (Moo::Keyboard::isDown(Moo::Keyboard::GodMode)) {
				player->toggleGodMode();
			}
			if (Moo::Keyboard::isDown(Moo::Keyboard::SizeUp)) {
				player->setHealth(player->getHealth() + 1);
				player->getSprite()->scale(Moo::Vector2f(0.1f, 0.1f));
				player->getHitboxSprite()->setScale(player->getSprite()->getScale());
			}
			if (Moo::Keyboard::isDown(Moo::Keyboard::SizeDown)) {
				player->setHealth(player->getHealth() - 1);
				player->getSprite()->scale(Moo::Vector2f(-0.1f, -0.1f));
				player->getHitboxSprite()->setScale(player->getSprite()->getScale());
			}

			if (Moo::Keyboard::isDown(Moo::Keyboard::Space)) {
				player->jump();
			}
			if (Moo::Keyboard::isPressed(Moo::Keyboard::Left))
				player->move(Direction::LEFT);
			if (Moo::Keyboard::isPressed(Moo::Keyboard::Right))
				player->move(Direction::RIGHT);
			if (Moo::Keyboard::isPressed(Moo::Keyboard::Up))
				Moo::d3d::getInstance().getCamera()->move(Moo::Vector2f(-10, 0));
			if (Moo::Keyboard::isPressed(Moo::Keyboard::Down))
				Moo::d3d::getInstance().getCamera()->move(Moo::Vector2f(10, 0));
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
					bulletPool.push_back(bullet);
					// Debug message
					//std::cout << "La taille de la bulletPool est de : " << bulletPool.size() << std::endl;

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
			
			player->setGravity(true);
			HitZone hitZone;
			Vector2f decal(0, 0);
		
			for (unsigned int i = 0; i < entities.size(); ++i)
			{
				if (entities[i].second->getGravity() == true)
					((Moo::Character *)entities[i].second)->update();
				if (entities[i].second != player
					&& entities[i].second->isCollidable()
					&& ((hitZone = player->collisionAABB(entities[i].second)) != HitZone::NONE))
				{
					//If we collide with an enemy : Absorb him
					if (_strnicmp(entities[i].first.c_str(), "Enemy", 5) == 0)
					{
						Moo::Character *enemyCollided = (Moo::Character *)entities[i].second;
						if (player->getHealth() > enemyCollided->getHealth() || player->isGodMode() == true)
						{
							player->setHealth(player->getHealth() + (enemyCollided->getHealth() * 33 / 100));
							player->getSprite()->scale(Moo::Vector2f(0.1f * (enemyCollided->getHealth() * 33 / 100), 0.1f * (enemyCollided->getHealth() * 33 / 100)));
							player->getHitboxSprite()->setScale(player->getSprite()->getScale());
							entities.erase(entities.begin() + i);
							std::cout << "Player health : " << player->getHealth() << std::endl;
						}
						else
						{
							Moo::Sprite *lose = new Moo::Sprite(
								400,
								133,
								(Moo::d3d::getInstance().getCamera()->getPosition().x *-1) +
								Moo::d3d::getInstance().getScreenSize().x / 2 - 250,
								(Moo::d3d::getInstance().getCamera()->getPosition().y *-1) +
								Moo::d3d::getInstance().getScreenSize().y / 2
								);
							audio.pauseSound(music);
							audio.playSound(soundLose, false);
							lose->loadTexture(loseText);
							window.draw(lose);
							window.display();
							Sleep(1000);
							audio.pauseSound(soundLose);

							Game::getInstance().runScene(TypeScene::MENU, TypeScene::LEVEL, window);
							return false;
						}
					}
					//If we collide with an Exit
					else if (_strnicmp(entities[i].first.c_str(), "Exit", 4) == 0)
					{
						Moo::Sprite *win = new Moo::Sprite(
							400,
							133,
							(Moo::d3d::getInstance().getCamera()->getPosition().x *-1) +
							Moo::d3d::getInstance().getScreenSize().x / 2 - 200,
							(Moo::d3d::getInstance().getCamera()->getPosition().y *-1) +
							Moo::d3d::getInstance().getScreenSize().y / 2
							);
						audio.pauseSound(music);
						audio.playSound(soundWin, false);
						win->loadTexture(winText);
						window.draw(win);
						window.display();
						Sleep(1000);
						audio.pauseSound(soundWin);
						Game::getInstance().runScene(TypeScene::MENU, TypeScene::LEVEL, window);
						return false;
					}
					//If we collide with a wall/platform/bottom
					else
					{
						if (hitZone == HitZone::RIGHT_SIDE)
							decal.x = entities[i].second->getHitbox().x1 - player->getHitbox().x2;
						else if (hitZone == HitZone::LEFT_SIDE)
							decal.x = entities[i].second->getHitbox().x2 - player->getHitbox().x1;
						else if (hitZone == HitZone::TOP)
						{
							decal.y = entities[i].second->getHitbox().y2 - player->getHitbox().y1;
							player->setVelocity(Vector2f(player->getVelocity().x, -1));
						}
						else
						{
							decal.y = entities[i].second->getHitbox().y1 - player->getHitbox().y2;
							player->resetPos();
							player->setGravity(false);
						}
					}
				}
			}

			// UPDATE CAMERA
			Moo::d3d::getInstance().getCamera()->update(player->getHitbox());

			if (decal.y != 0)
				player->getSprite()->setY(player->getSprite()->getY() + decal.y);
			if (decal.x != 0)
				player->getSprite()->setX(player->getSprite()->getX() + decal.x);
			player->resetHitbox();

			window.clear();
			window.draw(background);

			// Display hitbox if godmode is on
			if (player->isGodMode() == true)
				window.draw(player->getHitboxSprite());

			for (unsigned int i = 0; i < entities.size(); ++i)
			{
				window.draw(((Moo::Character *)entities[i].second)->getSprite());
				window.draw(((Moo::Character *)entities[i].second)->getHitboxSprite());
				if (_strnicmp(entities[i].first.c_str(), "Enemy", 5) == 0)
					((Moo::Character *)entities[i].second)->getSprite()->rotate(1);
			}

			for (unsigned int i = 0; i < bulletPool.size(); ++i)
			{
				Moo::Bullet *bullet = bulletPool[i];
				bullet->move(Direction::RIGHT);
				HitZone hitZone;
				/*
				if (bulletPool[i]->getGravity() == true)
					((Moo::Character *)bulletPool[i])->update();
				*/
				for (unsigned int j = 0; j < entities.size(); ++j)
					if (entities[i].second != player
					&& (hitZone = bullet->collisionAABB(entities[j].second)) != HitZone::NONE
					&& entities[j].second->isCollidable())
					{
						bulletPool.erase(bulletPool.begin() + i);
						if (_strnicmp(entities[j].first.c_str(), "Enemy", 5) == 0)
						{
							Moo::Character *enemy = (Moo::Character *)entities[j].second;
							if (enemy->getHealth() < 10)
								enemy->setHealth(enemy->getHealth() + 1);
							enemy->getSprite()->scale(Moo::Vector2f(0.1f, 0.1f));
							enemy->getHitboxSprite()->setScale(enemy->getSprite()->getScale());
							//std::cout << "Enemy health : " << ((Moo::Character *)entities[j].second)->getHealth() << std::endl;
						}
					}

				window.draw(bullet->getSprite());
				window.draw(bullet->getHitboxSprite());
			}
			window.display();
		}
		audio.pauseSound(music);
		//backgroundText->release();

		return false;
	}
}