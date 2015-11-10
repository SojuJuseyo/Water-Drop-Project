#include "Character.h"

namespace Moo
{
	Character::Character(Vector2f velocity, float mass, Sprite *sprite, bool hasGravity)
	{
		this->setVelocity(velocity);
		this->setMass(mass);
		this->_sprite = sprite;
		this->setHitbox(sprite->getX(), sprite->getX() + sprite->getWidth(), sprite->getY(), sprite->getY() - sprite->getHeight());
		this->_acceleration.y = this->_mass / FPS_LIMIT;
		this->setGravity(hasGravity);
		_hitboxSprite = new Sprite(*_sprite);
		_hitboxSprite->loadTexture("hitbox.dds");
	}

	Character::~Character()
	{
	}

	Hitbox Character::resetHitbox()
	{
		_hitbox.x1 = this->_sprite->getX();
		_hitbox.y1 = this->_sprite->getY();
		_hitbox.x2 = this->_sprite->getX() + this->_sprite->getWidth();
		_hitbox.y2 = this->_sprite->getY() - this->_sprite->getHeight();

		return _hitbox;
	}

	void	Character::move(Direction direction)
	{
		if (direction == Direction::LEFT)
		{
			_sprite->move(-_velocity.x, 0);
		}
		else
		{
			_sprite->move(_velocity.x, 0);
		}
	}

	void	Character::jump()
	{
		if (_velocity.y == 0)
			this->setVelocity(Vector2f(_velocity.x, JUMP_VELOCITY));
	}

	void	Character::resetPos()
	{
		_velocity.y = 0;
		_acceleration.y = _mass / FPS_LIMIT;
	}

	void	Character::update()
	{
		if (_velocity.y > 0 && _velocity.y < GRAVITY)
			_acceleration.y = _mass;
		_acceleration.y += (_mass / FPS_LIMIT);
		_velocity.y -= (_velocity.y + _acceleration.y) / FPS_LIMIT;
		_sprite->setY(_sprite->getY() + (_velocity.y - GRAVITY) / FPS_LIMIT);
	}

	HitZone Character::collisionAABB(Entity *entity)
	{
		Hitbox A = this->resetHitbox();
		Hitbox B = entity->getHitbox();

		if (A.y2 < B.y1 && A.y2 > B.y2 && ((A.x2 < B.x2 && A.x2 > B.x1) || (A.x1 < B.x2 && A.x1 > B.x1)))
			return HitZone::BOTTOM;
		if (A.y1 > B.y2 && A.y1 < B.y1 && ((A.x2 < B.x2 && A.x2 > B.x1) || (A.x1 < B.x2 && A.x1 > B.x1)))
			return HitZone::TOP;
		if (A.x2 < B.x2 && A.x2 > B.x1 && ((A.y2 <= B.y1 && A.y2 >= B.y2) || (A.y1 <= B.y2 && A.y1 >= B.y1)))
			return HitZone::RIGHT_SIDE;
		if (A.x1 < B.x2 && A.x1 > B.x1 && ((A.y2 >= B.y1 && A.y2 <= B.y2) || (A.y1 >= B.y2 && A.y1 <= B.y1)))
			return HitZone::LEFT_SIDE;
		return (HitZone::NONE);
	}

	Sprite	*Character::getSprite() const
	{
		return _sprite;
	}

	Sprite	*Character::getHitboxSprite() const
	{
		_hitboxSprite->setPosition(_sprite->getPosition());

		return _hitboxSprite;
	}
}