#pragma once

#include "Window.h"
#include "Keyboard.h"
#include "d3d.h"
#include "Fps.h"
#include "Vector2f.h"
#include "Character.h"
#include "Sprite.h"
#include "Text.h"
#include "JsonParser.h"
#include "Bullet.h"

#include <vector>

static std::vector<std::pair<std::string, Moo::Entity *>>	getEntitiesFromMap(JsonParser *map)
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

	//Because the map created by the map editor are not in WINDOW_HEIGHT * WINDOW_WIDTH resolution
	float multHeight = WINDOW_HEIGHT / map->getMap().getMapHeight();
	float multWidth = WINDOW_WIDTH / map->getMap().getMapWidth();

	std::cout << "multHeight: " << multHeight << std::endl;
	std::cout << "multWidth: " << multWidth << std::endl;

	//counter
	int i = 1;

	//Player specs
	float playerHeight = 60;
	float playerWidth = 60;
	float playerMass = 300;

	//Enemies specs
	float enemiesHeight = 60;
	float enemiesWidth = 60;
	float enemiesMass = 100;

	//Enemies
	for (std::list<Tile *>::const_iterator it = enemyTiles.begin(); it != enemyTiles.end(); ++it)
	{
		Moo::Sprite *enemySprite = new Moo::Sprite(enemiesWidth, enemiesHeight, (*it)->getPosX() * multWidth, (*it)->getPosY() * multHeight);
		enemySprite->loadTexture(marioText);
		Moo::Character *enemy = new Moo::Character(Moo::Vector2f(1, 0), enemiesMass, enemySprite, false);
		enemy->setCollision(true);
		entities.push_back(std::make_pair("Enemy " + std::to_string(i), enemy));
		++i;
	}

	//reset counter
	i = 1;

	//platforms
	for (std::list<Tile *>::const_iterator it = platformTiles.begin(); it != platformTiles.end(); ++it)
	{
		Moo::Sprite *platform = new Moo::Sprite(multWidth, multHeight, (*it)->getPosX() * multWidth, (*it)->getPosY() * multHeight);
		platform->loadTexture(platformText);
		Moo::Character *platformEntity = new Moo::Character(Moo::Vector2f(1, 0), 0, platform, false);
		entities.push_back(std::make_pair("Platform " + std::to_string(i), platformEntity));
		++i;
	}

	//bottom
	for (std::list<Tile *>::const_iterator it = bottomTiles.begin(); it != bottomTiles.end(); ++it)
	{
		Moo::Sprite *ground = new Moo::Sprite(multWidth, multHeight, (*it)->getPosX() * multWidth, (*it)->getPosY() * multHeight);
		ground->loadTexture(groundText);
		entities.push_back(std::make_pair("Bottom", new Moo::Character(Moo::Vector2f(1, 0), 0, ground, false)));
	}

	if (playerTiles.size() > 0)
	{
		//Get the first element because there is only one player
		std::list<Tile *>::const_iterator playerIt = playerTiles.begin();

		//Player
		Moo::Sprite *mario = new Moo::Sprite(playerWidth, playerHeight, (*playerIt)->getPosX() * multWidth, (*playerIt)->getPosY() * multHeight);
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

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) 
{
	//To display std::cout output
	FILE * pConsole;
	AllocConsole();
	freopen_s(&pConsole, "CONOUT$", "wb", stdout);

	//Getting the game window
	Moo::Window window(hInstance, Moo::WindowSettings("Water Drop"));
	
	//Text class to display fps counter
	Moo::Text *text = new Moo::Text("Text", 20, 20, 20, 0);

	Moo::Texture *backgroundText = new Moo::Texture;
	backgroundText->loadFromFile("background.dds");

	std::vector<std::pair<std::string, Moo::Entity *>> entities;
	try
	{
		//We get the map
		JsonParser *map = new JsonParser("2d-Maps/test.json");

		if (map->parseFile() == -1)
			throw std::string("Can't load the map");
		//map->getMap().displayMapInfos();
	
		//Read the entities from the map
		entities = getEntitiesFromMap(map);
	}
	catch (std::string error)
	{
		std::cout << "Error: " << error << std::endl;
	}
	
	//background
	Moo::Sprite *background = new Moo::Sprite(WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0);
	background->loadTexture(backgroundText);

	HitZone tmp = HitZone::NONE;

	//60 FPS master race
	window.setFpsLimit(FPS_LIMIT);

	Moo::Character *player = (Moo::Character *)entities[0].second;

	//Bullet pool
	std::vector<Moo::Bullet *> bulletPool;
	// Temp texture for the bullet
	Moo::Texture *bulletText = new Moo::Texture;
	bulletText->loadFromFile("platform.dds");

	while (window.isOpen())
	{
		if (Moo::Keyboard::isPressed(Moo::Keyboard::Left))
			player->move(Direction::LEFT);
		else if (Moo::Keyboard::isPressed(Moo::Keyboard::Right))
			player->move(Direction::RIGHT);
		else if (Moo::Keyboard::isPressed(Moo::Keyboard::Space))
			player->jump();
		else if (Moo::Keyboard::isPressed(Moo::Keyboard::Up))
			Moo::d3d::getInstance().getCamera()->move(Moo::Vector2f(-10, 0));
		else if (Moo::Keyboard::isPressed(Moo::Keyboard::Shot))
		{
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
			std::cout << "La taille de la bulletPool est de : " << bulletPool.size() << std::endl;

			int currentHealth = player->getHealth();
			player->setHealth(currentHealth - 1);

			std::cout << "Player health : " << player->getHealth() << std::endl;
		}

		for (unsigned int i = 0; i < entities.size(); ++i)
			if (entities[i].second->getGravity() == true)
				((Moo::Character *)entities[i].second)->update();

		bool eraseCollider;
		for (unsigned int i = 1; i < entities.size(); ++i)
		{
			eraseCollider = false;
			//player->setGravity(true);
			while ((tmp = player->collisionAABB(entities[i].second)) != HitZone::NONE
				&& entities[i].second->isCollidable())
			{
				//If we collide with an enemy : Absorb him
				if (_strnicmp(entities[i].first.c_str(), "Enemy", 5) == 0)
				{
					player->getSprite()->scale(Moo::Vector2f(0.5f, 0.5f));
					player->getHitboxSprite()->setScale(player->getSprite()->getScale());
					eraseCollider = true;
				}
				//If we collide with a wall/platform/bottom
				else
				{
					std::cout << "COLLIDING with " << entities[i].first << " : ";
					if (tmp == HitZone::BOTTOM || tmp == HitZone::TOP)
					{
						if (tmp == HitZone::BOTTOM)
						{
							player->getSprite()->setY(entities[i].second->getHitbox().y1);
							player->resetPos();
							std::cout << "BOTTOM";
							player->setGravity(false);
						}
						else
						{
							player->getSprite()->setY(entities[i].second->getHitbox().y2 - player->getSprite()->getHeight());
							player->setVelocity(Moo::Vector2f(player->getVelocity().x, -1));
							std::cout << "TOP";
						}
					}
					else
					{
						if (tmp == HitZone::RIGHT_SIDE)
						{
							std::cout << "RIGHT_SIDE";
							player->getSprite()->setX(entities[i].second->getHitbox().x1 - player->getSprite()->getWidth());
						}
						else
						{
							std::cout << "LEFT_SIDE";
							player->getSprite()->setX(entities[i].second->getHitbox().x2);
						}
					}
					std::cout << std::endl;
				}
				Moo::Hitbox collider = entities[i].second->getHitbox();
				std::cout << "Collider : [x1] " << collider.x1 << " && " << collider.y1 << " [y1] - [x2] " << collider.x2 << " && " << collider.y2 << " [y2]" << std::endl;
				std::cout << "Character before : [x1] " << player->getHitbox().x1 << " && " << player->getHitbox().y1 << " [y1] - [x2] " << player->getHitbox().x2 << " && " << player->getHitbox().y2 << " [y2]" << std::endl;
				player->resetHitbox();
				std::cout << "Character after : [x1] " << player->getHitbox().x1 << " && " << player->getHitbox().y1 << " [y1] - [x2] " << player->getHitbox().x2 << " && " << player->getHitbox().y2 << " [y2]" << std::endl;
				if (eraseCollider == true)
					entities.erase(entities.begin() + i);
			}
		}

		window.clear();
		window.draw(background);

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
			
			for (unsigned int j = 1; j < entities.size(); ++j)
				if ((tmp = bullet->collisionAABB(entities[j].second)) != HitZone::NONE && entities[j].second->isCollidable())
				{
					bulletPool.erase(bulletPool.begin() + i);
					if (_strnicmp(entities[j].first.c_str(), "Enemy", 5) == 0)
					{
						Moo::Character *enemy = (Moo::Character *)entities[j].second;
						((Moo::Character *)entities[j].second)->setHealth(enemy->getHealth() + 1);
						std::cout << "Enemy health : " << ((Moo::Character *)entities[j].second)->getHealth() << std::endl;
					}
				}

			window.draw(bullet->getSprite());
			window.draw(bullet->getHitboxSprite());
		}

		//text->setText(std::to_string(window.getFps()));
		//window.draw(text);
		window.display();
	}

	backgroundText->release();

	window.destroy();
	return 0;
}
