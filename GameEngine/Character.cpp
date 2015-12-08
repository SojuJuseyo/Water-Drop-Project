#include "Character.h"

namespace Moo
{
	Character::Character(Vector2f velocity, float mass, Sprite *sprite, bool hasGravity)
	{
		this->setVelocity(velocity);
		this->setMass(mass);
		this->_sprite = sprite;
		this->setHitbox(sprite->getX(), sprite->getY() + sprite->getHeight(), sprite->getX() + sprite->getWidth(), sprite->getY());//x1 y1 x2 y2
		this->_acceleration.y = this->_mass / FPS_LIMIT;
		this->setGravity(hasGravity);
		_hitboxSprite = new Sprite(*_sprite);
		Moo::Texture *hitbox = new Moo::Texture;
		hitbox->loadFromFile("hitbox.dds");
		_hitboxSprite->loadTexture(hitbox);

		this->_health = 10;
	}

	Character::~Character()
	{
	}

	Hitbox Character::resetHitbox()
	{
		_hitbox.x1 = this->_sprite->getX();
		_hitbox.y1 = this->_sprite->getY() + this->_sprite->getHeight();

		_hitbox.x2 = this->_sprite->getX() + this->_sprite->getWidth();
		_hitbox.y2 = this->_sprite->getY();

		return _hitbox;
	}

	HitZone		Character::collisionAABB(Entity *entity)
	{
		this->resetHitbox();
		return (Entity::collisionAABB(entity));
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
		if (this->_velocity.y == 0)
		{
			this->setVelocity(Vector2f(this->_velocity.x, JUMP_VELOCITY));
			this->setGravity(true);
		}
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

	Sprite	*Character::getSprite() const
	{
		return _sprite;
	}

	Sprite	*Character::getHitboxSprite() const
	{
		_hitboxSprite->setPosition(_hitbox.x1, _hitbox.y2);

		return _hitboxSprite;
	}

	void Character::setHealth(int _health)
	{
		this->_health = _health;
	}

	int	Character::getHealth() const
	{
		return (_health);
	}
}