#pragma once

#include <string>
#include <map>
#include "../Includes/Vector2f.h"

enum HitZone
{
	TOP,
	BOTTOM,
	LEFT_SIDE,
	RIGHT_SIDE,
	NONE
};

enum Direction
{
	LEFT,
	RIGHT
};

enum EntityType
{
	PLAYER,
	ENEMY,
	BULLET,
	BLOCK,
	PLATFORM,
	GROUND,
	EXIT,
	ENTRANCE
};

namespace Moo
{
	typedef struct Hitbox
	{
		//Top left
		float x1;
		float y1;
		//Bottom right
		float x2;
		float y2;
	}			   Hitbox;

	class Entity
	{
	public:
		Entity();
		virtual ~Entity() {}

		void setHitbox(float, float, float, float);
		void setCollision(bool);

		Hitbox				getHitbox() const;
		EntityType			getEntityType() const;
		bool				isCollidable() const;
		HitZone				collisionAABB(Entity *entity);

	protected:
		Hitbox				_hitbox;
		bool				_isCollidable;
		EntityType			_type;
	};
}