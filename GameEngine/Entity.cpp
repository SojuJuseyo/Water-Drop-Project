#include "Entity.h"
#include <iostream>

namespace Moo
{
	Entity::Entity() : _isCollidable(true)
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

	void Entity::setCollision(bool collision)
	{
		_isCollidable = collision;
	}

	void Entity::setHitbox(float x1, float y1, float x2, float y2)
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

	bool Entity::isCollidable() const
	{
		return _isCollidable;
	}

	Hitbox Entity::getHitbox() const
	{
		return _hitbox;
	}

	HitZone Entity::collisionAABB(Entity *entity)
	{
		Hitbox A = this->getHitbox();
		Hitbox B = entity->getHitbox();
		float CollideHeightOfB = (B.y1 - B.y2) / 6;

		if (A.y2 < B.y1 && A.y2 > B.y2 && (B.y1 - A.y2 < CollideHeightOfB) && ((A.x1 <= B.x2 && A.x1 >= B.x1) || (A.x2 <= B.x2 && A.x2 >= B.x1)))
			return HitZone::BOTTOM;
		if (A.y1 > B.y2 && A.y1 < B.y1 && (A.y1 - B.y2 < CollideHeightOfB) && ((A.x1 <= B.x2 && A.x1 >= B.x1) || (A.x2 <= B.x2 && A.x2 >= B.x1)))
			return HitZone::TOP;
		if (A.x2 < B.x2 && A.x2 > B.x1 && ((A.y1 > B.y2 && A.y1 < B.y1) || (A.y2 < B.y1 && A.y2 > B.y2) || (A.y1 > B.y1 && A.y2 < B.y2) || (A.y1 < B.y1 && A.y2 > B.y2)))
			return HitZone::RIGHT_SIDE;
		if (A.x1 < B.x2 && A.x1 > B.x1 && ((A.y1 > B.y2 && A.y1 < B.y1) || (A.y2 < B.y1 && A.y2 > B.y2) || (A.y1 > B.y1 && A.y2 < B.y2) || (A.y1 < B.y1 && A.y2 > B.y2)))
			return HitZone::LEFT_SIDE;

		return (HitZone::NONE);
	}
}