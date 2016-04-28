#pragma once

#include "Includes/WindowSettings.h"
#include "Includes/Vector2f.h"
#include "Includes/DynamicEntity.h"
#include "Includes/Sprite.h"

namespace Moo
{
	class Bullet : public DynamicEntity
	{
	public:
		Bullet(std::shared_ptr<Sprite>, float, float);
		virtual ~Bullet();

		HitZone	collisionAABB(Entity *entity);
	};
}