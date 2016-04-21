#pragma once

#include <ctime>
#include <chrono>

#include "Scene.h"
#include "JsonParser.h"
#include "Bullet.h"
#include "Game.h"
#include "Character.h"
#include "SoundSystem.h"
#include "Camera.h"

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
		bool	runUpdate();
		void	clean();
		bool	init(std::shared_ptr<Moo::Window> window);
		void	getEntitiesFromMap(JsonParser *map);
		Camera	getCamera();
		void	inputHandling();
		void	displayHitboxesAndSprites();
		void	applyGravityAndCollisions();
		void	exitReached();
		void	playerDead();

	private:
		std::vector<std::pair<std::string, Moo::Entity *>> staticEntities;
		std::vector<std::pair<std::string, Moo::Entity *>> dynamicEntities;
		JsonParser						*map;
		Moo::Character					*player;
		std::vector<Moo::Bullet *>		bulletPool;
		Moo::Sprite						*background, *lose, *win;
		Moo::Texture					*bulletText, *loseText, *winText, *backgroundText;
		std::shared_ptr<Window>			_window;
		std::shared_ptr<SoundSystem>	 _soundSystem;
		Moo::Camera						_camera;
		FMOD::Channel					*themeChan;
		bool							_triedJump;
		std::chrono::time_point<std::chrono::system_clock> _startTime, _canTemporarilyJump;
	};
}