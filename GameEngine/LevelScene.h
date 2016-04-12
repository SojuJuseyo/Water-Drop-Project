#pragma once

#include "Scene.h"
#include "JsonParser.h"
#include "Bullet.h"
#include "Game.h"
#include "Character.h"
#include "Audio.h"
#include "SoundSystem.h"

struct s_collider
{
	bool		isCollideUp;
	bool		isCollideDown;
	bool		isCollideRight;
	bool		isCollideLeft;
};


namespace Moo
{
	class LevelScene : public Scene
	{
	public:
		LevelScene();
		~LevelScene();
		bool	run(Moo::Window &window);
		void	clean();
		bool	init(SoundSystem *soundsystem);
		void	getEntitiesFromMap(JsonParser *map);
		bool	inputHandling(Moo::Window &window);
		void	displayHitboxesAndSprites(Moo::Window &window);
		bool	applyGravityAndCollisions(Moo::Window &window);
		void	exitReached(Moo::Window &window);
		void	playerDead(Moo::Window &window);

	private:
		std::vector<std::pair<std::string, Moo::Entity *>> staticEntities;
		std::vector<std::pair<std::string, Moo::Entity *>> dynamicEntities;
		JsonParser					*map;
		Moo::Character				*player;
		std::vector<Moo::Bullet *>	bulletPool;
		Moo::Sprite					*background, *lose, *win;
		Moo::Texture				*bulletText, *loseText, *winText, *backgroundText;
		//Moo::Sound					music, jump, soundWin, soundLose;
		//Moo::Audio audio;
		Moo::Camera camera;
		FMOD::Channel *themeChan;
		bool						_triedJump;
		SoundSystem					*soundSystem;
	};
}