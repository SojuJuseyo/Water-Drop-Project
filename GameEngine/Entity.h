#pragma once

#include "Vector2f.h"
#define	GRAVITY	200
#define	JUMP_VELOCITY	1000

namespace Moo
{
	typedef struct Hitbox
	{
		//Top right
		float x1;
		float y1;
		//Bottom left
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

	protected:
		Vector2f	_velocity;
		float		_mass;
		Hitbox		_hitbox;
		Vector2f	_acceleration;
		bool		_isCollidable;
		bool		_hasGravity;
	};
}