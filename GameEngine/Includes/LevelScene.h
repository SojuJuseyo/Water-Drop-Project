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
#include "Text.h"

namespace Moo
{
	class LevelScene : public Scene
	{
	public:
		LevelScene(const std::string &);
		~LevelScene();

		std::string		getEntityTypeName(EntityType);
		bool			runUpdate();
		void			clearEntityType(EntityType, bool);
		void			clean();
		void			getEntitiesFromMap(std::shared_ptr<MapInfos> map);
		void			fillStaticEntitiesList(EntityType, Tile, bool);
		void			fillDynamicEntitiesList(int, EntityType, float, float, float, float, float, float, bool, Direction, TileProperties);
		Camera			getCamera();
		bool			init(std::shared_ptr<Window> window, std::map<std::string, Texture>);
		void			inputHandling();
		bool			isVisible(Entity, Entity, float);
		void			displayHitboxesAndSprites();
		void			applyGravityAndCollisions();
		void			exitReached();
		void			loadFromSpriteSheet();
		void			playerDead();
		void			updateScriptsStatic();
		Vector2f		updateScriptDynamic(std::shared_ptr<DynamicEntity>, Vector2f);
		FMOD::Channel	*themeChan;

	private:
		std::vector<std::shared_ptr<Moo::StaticEntity>>		_staticEntities;
		std::vector<std::shared_ptr<Moo::DynamicEntity>>	_dynamicEntities;
		std::map<EntityType, std::string>					_entityTypeName;
		std::shared_ptr<Moo::Font> _font;
		std::shared_ptr<Moo::Text> _fps;

		std::shared_ptr<MapInfos>							_map;
		std::shared_ptr<std::map<std::string, Texture>>		_textures;
		std::map<std::string, Moo::Vector2f>				_spriteSheet;
		std::shared_ptr<Moo::Character>						_player;
		std::shared_ptr<Moo::Sprite>						_background, _lose, _win;
		std::shared_ptr<Window>								_window;
		std::shared_ptr<SoundSystem>						_soundSystem;
		Moo::Camera											_camera;
		bool												_triedJump, _exitReached, _playerDead;
		std::chrono::time_point<std::chrono::system_clock>	_startTime, _lastJump, _canTemporarilyJump;
		std::string											_pathMapFile;
	};
}