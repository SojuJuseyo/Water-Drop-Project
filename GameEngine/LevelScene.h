#pragma once

#include "Scene.h"
#include "JsonParser.h"
#include "Bullet.h"
#include "Game.h"
#include "Character.h"
#include "Audio.h"

namespace Moo
{
	class LevelScene : public Scene
	{
	public:
		LevelScene();
		~LevelScene();
		bool	run(Moo::Window &window);
		void	clean();
		bool	init();
		std::vector<std::pair<std::string, Moo::Entity *>> getEntitiesFromMap(JsonParser *map);
	private:
		std::vector<std::pair<std::string, Moo::Entity *>> entities;
		JsonParser *map;
		Moo::Sprite *background;
		HitZone tmp;
		Moo::Character *player;
		std::vector<Moo::Bullet *> bulletPool;
		Moo::Texture *bulletText;
		Moo::Sound music;
		Moo::Sound jump;
		Moo::Sound soundWin;
		Moo::Sound soundLose;
		Moo::Audio audio;
		Moo::Texture *backgroundText;
		Moo::Camera camera;
		Moo::Texture *loseText;
		Moo::Texture *winText;
	};
}