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
		LevelScene(std::string mapFile);		// desormais quand on cree un levelscene (qui va correspondre a un niveau), on precise la map
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
		FMOD::Channel					*themeChan;

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
		bool							_triedJump, _exitReached, _playerDead;
		std::chrono::time_point<std::chrono::system_clock> _startTime, _lastJump, _canTemporarilyJump;
		std::string						_mapFilePath;
	};
}