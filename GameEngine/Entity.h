#pragma once

#include "Vector2f.h"
#define	GRAVITY	200
#define	JUMP_VELOCITY	750

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

		void setVelocity(Vector2f);
		void setMass(float);
		void setHitbox(float, float, float, float);
		void setGravity(bool);
		void setCollision(bool);

		Vector2f	getVelocity() const;
		float		getMass() const;
		Hitbox		getHitbox() const;
		bool		getGravity() const;
		bool		isCollidable() const;
		HitZone		collisionAABB(Entity *entity);

	protected:
		Vector2f	_velocity;
		float		_mass;
		Hitbox		_hitbox;
		Vector2f	_acceleration;
		bool		_isCollidable;
		bool		_hasGravity;
	};
}