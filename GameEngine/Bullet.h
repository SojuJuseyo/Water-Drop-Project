#pragma once

#include "WindowSettings.h"
#include "Vector2f.h"
#include "DynamicEntity.h"
#include "Sprite.h"

namespace Moo
{
	class Bullet : public DynamicEntity
	{
	public:
		Bullet(Sprite *, float, float, std::string);
		virtual ~Bullet();

		HitZone	collisionAABB(Entity *entity);
	};
}