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
		bool run(Moo::Window &window);
		void clean();
		std::vector<std::pair<std::string, Moo::Entity *>> getEntitiesFromMap(JsonParser *map);
	private:

	};
}