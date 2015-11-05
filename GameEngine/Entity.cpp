#include "Entity.h"
#include <iostream>

namespace Moo
{
	Entity::Entity()
	{
	}

	void Entity::setVelocity(Vector2f velocity)
	{
		_velocity = velocity;
	}

	void Entity::setMass(float mass)
	{
		_mass = mass;
	}

	void Entity::setGravity(bool hasGravity)
	{
		_hasGravity = hasGravity;
	}

	void Entity::setHitbox(float x1, float x2, float y1, float y2)
	{
		_hitbox.x1 = x1;
		_hitbox.y1 = y1;
		_hitbox.x2 = x2;
		_hitbox.y2 = y2;
	}

	Vector2f Entity::getVelocity() const
	{
		return _velocity;
	}

	float Entity::getMass() const
	{
		return _mass;
	}

	bool Entity::getGravity() const
	{
		return _hasGravity;
	}

	Hitbox Entity::getHitbox() const
	{
		return _hitbox;
	}
}