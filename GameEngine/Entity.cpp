#include "Entity.h"

namespace Moo
{
	Entity::Entity()
	{
	}

	void Entity::setVelocity(float velocity)
	{
		_velocity = velocity;
	}

	void Entity::setMass(float mass)
	{
		_mass = mass;
	}

	void Entity::setHitbox(Hitbox hitbox)
	{
		_hitbox = hitbox;
	}

	float Entity::getVelocity() const
	{
		return _velocity;
	}

	float Entity::getMass() const
	{
		return _mass;
	}

	Hitbox Entity::getHitbox() const
	{
		return _hitbox;
	}
}