#pragma once

#include <ctime>
#include <chrono>

#include "Scene.h"
#include "JsonParser.h"
#include "Bullet.h"
#include "Game.h"
#include "Character.h"
#include "StaticEntity.h"
#include "SoundSystem.h"
#include "Camera.h"

namespace Moo
{
	class LevelScene : public Scene
	{
	public:
		LevelScene(const std::string &);
		~LevelScene();

		std::string	getEntityTypeName(EntityType);
		bool	runUpdate();
		void	clean();
		void	getEntitiesFromMap(std::shared_ptr<MapInfos> map);
		void	fillStaticEntitiesList(EntityType, float, float);
		void	fillDynamicEntitiesList(int, EntityType, float, float, float, float, float, float, bool, Direction);
		Camera	getCamera();
		bool	init(std::shared_ptr<Window> window, std::map<std::string, Texture>);
		void	inputHandling();
		void	displayHitboxesAndSprites();
		void	applyGravityAndCollisions();
		void	exitReached();
		void	loadFromSpriteSheet();
		void	playerDead();
		FMOD::Channel					*themeChan;

	private:
		std::vector<std::shared_ptr<Moo::StaticEntity>>		_staticEntities, _saveStaticEntities;
		std::vector<std::shared_ptr<Moo::DynamicEntity>>	_dynamicEntities, _saveDynamicEntities;
		std::map<EntityType, std::string>					_entityTypeName;

		std::shared_ptr<MapInfos>			_map;
		std::shared_ptr<std::map<std::string, Texture>> _textures;
		std::map<std::string, Moo::Vector2f> _spriteSheet;
		std::shared_ptr<Moo::Character>	_player;
		std::shared_ptr<Moo::Sprite>	_background, _lose, _win;
		std::shared_ptr<Window>			_window;
		std::shared_ptr<SoundSystem>	_soundSystem;
		Moo::Camera						_camera;
		bool							_triedJump, _exitReached, _playerDead;
		std::chrono::time_point<std::chrono::system_clock> _startTime, _lastJump, _canTemporarilyJump;
		std::string _pathMapFile;
	};
}