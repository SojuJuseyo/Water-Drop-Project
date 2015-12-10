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
		float CollideWidthOfB = (B.x2 - B.x1) / 8;

		//Check collision on Y
		if ((A.x1 <= B.x2 && A.x1 >= B.x1 && (B.x2 - A.x1 >= CollideWidthOfB)) ||	//We have to be colliding also with more than CollideWidthOfB on the left
			(A.x2 <= B.x2 && A.x2 >= B.x1 && (A.x2 - B.x1 >= CollideWidthOfB)) ||  //Or on the right
			(A.x1 < B.x1 && A.x2 > B.x2) ||										//Or to be bigger (width) than the collider 
			(A.x1 > B.x1 && A.x2 < B.x2) ||										//Or to be smaller (width) than the collider
			(A.x1 == B.x1 && A.x2 == B.x2))										//Or to be on the exact same X
		{
			if (A.y1 > B.y2 && A.y1 < B.y1 && (A.y1 - B.y2 <= CollideHeightOfB)) //Collison with top & the depth of the collision is less than CollideHeightOfB
				return HitZone::TOP;
			if (A.y2 < B.y1 && A.y2 > B.y2 && (B.y1 - A.y2 <= CollideHeightOfB)) //Collison with top & the depth of the collision is less than CollideHeightOfB
				return HitZone::BOTTOM;
		}
		
		//Check a collision on X
		if ((A.y1 > B.y2 && A.y1 < B.y1 && (A.y1 - B.y2 > CollideHeightOfB)) ||		//We have to be colliding with the top
			(A.y2 < B.y1 && A.y2 > B.y2 && (B.y1 - A.y2 > CollideHeightOfB)) ||		//Or with the bottom
			(A.y1 > B.y1 && A.y2 < B.y2) ||		//Or to be bigger than the collider
			(A.y1 < B.y1 && A.y2 > B.y2) ||		//Or to be smaller than the collider
			(A.y1 == B.y1 && A.y2 == B.y2))		//Or to be on the exact same Y
		{
			if (A.x1 < B.x2 && A.x1 > B.x1)     //Collision with the left side
				return HitZone::LEFT_SIDE;
			if (A.x2 < B.x2 && A.x2 > B.x1)     //Collision with the right side
				return HitZone::RIGHT_SIDE;
		}

		//We didn't find any collision
		return (HitZone::NONE);
	}
}