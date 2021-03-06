#include "Entity.h"
#include <iostream>

namespace Moo
{
	Entity::Entity()
	{
		_isActivated = true;
		_isScripted = false;
		_scriptDirection = ScriptDirection::STILL;
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

	void Entity::setHitboxLastPos(float x1, float y1, float x2, float y2)
	{
		_hitboxLastPos.x1 = x1;
		_hitboxLastPos.y1 = y1;
		_hitboxLastPos.x2 = x2;
		_hitboxLastPos.y2 = y2;
	}

	void Entity::setHitboxFirstPos(Hitbox hitbox)
	{
		_hitboxFirstPos = hitbox;
	}

	EntityType Entity::getEntityType() const
	{
		return _type;
	}

	bool Entity::isCollidable() const
	{
		return _isCollidable;
	}

	Hitbox Entity::getHitbox() const
	{
		return _hitbox;
	}

	Hitbox Entity::getHitboxLastPos() const
	{
		return _hitboxLastPos;
	}

	Hitbox Entity::getHitboxFirstPos() const
	{
		return _hitboxFirstPos;
	}

	HitZone Entity::collisionAABB(Entity *entity)
	{
		Hitbox A = this->getHitbox();
		Hitbox B = entity->getHitbox();
		float CollideHeightOfB = (B.y1 - B.y2) / 4;
		float CollideWidthOfB = (B.x2 - B.x1) / 5;

		//Check collision on Y
		if ((A.x1 <= B.x2 && A.x1 >= B.x1 && (B.x2 - A.x1 >= CollideWidthOfB)) ||	//We have to be colliding also with more than CollideWidthOfB on the left
			(A.x2 <= B.x2 && A.x2 >= B.x1 && (A.x2 - B.x1 >= CollideWidthOfB)) ||  //Or on the right
			(A.x1 < B.x1 && A.x2 >= B.x2) ||										//Or to be bigger (width) than the collider 
			(A.x1 > B.x1 && A.x2 <= B.x2) ||										//Or to be smaller (width) than the collider
			(A.x1 == B.x1 && A.x2 == B.x2) ||										//Or to be on the exact same X
			(A.x2 > B.x2 && A.x1 == B.x1))
		{
			if (A.y1 > B.y2 && A.y1 < B.y1 && (A.y1 - B.y2 <= CollideHeightOfB) //Collison with top & the depth of the collision is less than CollideHeightOfB
			 || A.y2 < B.y2 && A.y1 == B.y1)
				return HitZone::TOP;
			if (A.y2 < B.y1 && A.y2 >= B.y2 && (B.y1 - A.y2 <= CollideHeightOfB) //Collison with top & the depth of the collision is less than CollideHeightOfB
			 || A.y1 > B.y1 && A.y2 == B.y2)
				return HitZone::BOTTOM;
		}
		
		//Check a collision on X
		if ((A.y1 > B.y2 && A.y1 < B.y1 && (A.y1 - B.y2 > CollideHeightOfB)) ||		//We have to be colliding with the top
			(A.y2 < B.y1 && A.y2 > B.y2 && (B.y1 - A.y2 > CollideHeightOfB)) ||		//Or with the bottom
			(A.y1 > B.y1 && A.y2 <= B.y2) ||		//Or to be bigger than the collider
			(A.y1 < B.y1 && A.y2 >= B.y2) ||		//Or to be smaller than the collider
			(A.y1 == B.y1 && A.y2 == B.y2)) 	//Or to be on the exact same Y
		{
			if (A.x1 < B.x2 && A.x1 > B.x1)     //Collision with the left side
				return HitZone::LEFT_SIDE;
			if (A.x2 < B.x2 && A.x2 > B.x1)     //Collision with the right side
				return HitZone::RIGHT_SIDE;
		}

		//We didn't find any collision
		return (HitZone::NONE);
	}

	bool				Entity::getIsActivated() const
	{
		return _isActivated;
	}

	void				Entity::setIsActivated(bool isActivated)
	{
		this->_isActivated = isActivated;
	}

	bool				Entity::getIsScripted() const
	{
		return _isScripted;
	}

	void				Entity::setIsScripted(bool isScripted)
	{
		this->_isScripted = isScripted;
	}

	ScriptDirection		Entity::getScriptDirection() const
	{
		return _scriptDirection;
	}

	void				Entity::setScriptDirection(ScriptDirection scriptDirection)
	{
		this->_scriptDirection = scriptDirection;
	}
}