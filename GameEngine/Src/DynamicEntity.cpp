#include "DynamicEntity.h"

namespace Moo
{
	DynamicEntity::DynamicEntity()
	{
	}

	Vector2f DynamicEntity::getVelocity() const
	{
		return _velocity;
	}

	float DynamicEntity::getMass() const
	{
		return _mass;
	}

	bool DynamicEntity::getGravity() const
	{
		return _hasGravity;
	}

	void DynamicEntity::setVelocity(Vector2f velocity)
	{
		_velocity = velocity;
	}

	void DynamicEntity::setMass(float mass)
	{
		_mass = mass;
	}

	void DynamicEntity::setGravity(bool hasGravity)
	{
		_hasGravity = hasGravity;
	}

	Sprite	*DynamicEntity::getSprite() const
	{
		return _sprite.get();
	}

	Sprite	*DynamicEntity::getHitboxSprite()
	{
		_hitboxSprite->setPosition(_hitbox.x1, _hitbox.y2);

		return _hitboxSprite.get();
	}

	void DynamicEntity::setHealth(float _health)
	{
		this->_health = _health;
	}

	float	DynamicEntity::getHealth() const
	{
		return (_health);
	}

	Hitbox DynamicEntity::resetHitbox()
	{
		_hitbox.x1 = this->_sprite->getX();
		_hitbox.y1 = this->_sprite->getY() + this->_sprite->getHeight();

		_hitbox.x2 = this->_sprite->getX() + this->_sprite->getWidth();
		_hitbox.y2 = this->_sprite->getY();

		return _hitbox;
	}

	HitZone		DynamicEntity::collisionAABB(Entity *entity)
	{
		this->resetHitbox();
		return (Entity::collisionAABB(entity));
	}

	void	DynamicEntity::resetPos()
	{
		_velocity.y = 0;
		_acceleration.y = _mass / FPS_LIMIT;
	}

	void	DynamicEntity::changeHealth(float value)
	{
		this->setHealth(this->_health + value);
		this->_sprite->scale(Moo::Vector2f(value / 10, value / 10));
		this->_hitboxSprite->setScale(this->_sprite->getScale());
		this->resetHitbox();
	}

	void	DynamicEntity::evaporateHeatZone()
	{
			this->changeHealth((float)(EVAPORATION_RATE / FPS_LIMIT));
	}
}