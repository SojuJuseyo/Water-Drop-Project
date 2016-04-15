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
		_texture = new Moo::Texture;
		_texture->loadFromFile("hitbox.dds");
		_hitboxSprite->loadTexture(_texture);

		this->_health = 5;

		this->_godMode = false;
	}

	Character::~Character()
	{
		if (_sprite != nullptr)
			delete _sprite;
		if (_hitboxSprite != nullptr)
			delete _hitboxSprite;
		if (_texture != nullptr)
			_texture->release();
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
		if ((this->getVelocity().x <= STANDARD_VELOCITY_X && this->getVelocity().x >= -STANDARD_VELOCITY_X) || this->getVelocity().y < 0)
		{
			if (direction == Direction::LEFT)
				this->setVelocity(Vector2f(-STANDARD_VELOCITY_X, this->getVelocity().y));
			else
				this->setVelocity(Vector2f(STANDARD_VELOCITY_X, this->getVelocity().y));
		}
		else
			std::cout << "Wait your velocity X is: " << this->getVelocity().x << std::endl;
	}

	bool	Character::jump(bool forced)
	{
		if (this->_velocity.y == 0 || forced == true)
		{
			if (forced == false)
				this->setVelocity(Vector2f(this->_velocity.x, JUMP_VELOCITY * 1.5f));
			else
				this->setVelocity(Vector2f(this->_velocity.x, this->_velocity.y + JUMP_VELOCITY * 1.5f));
			this->setGravity(true);
			return (true);
		}
		return (false);
	}

	void	Character::resetPos()
	{
		_velocity.y = 0;
		_acceleration.y = _mass / FPS_LIMIT;
	}

	void	Character::update()
	{
		//Updating Y velocity
		if (_velocity.y > 0 && _velocity.y < GRAVITY)
			_acceleration.y = _mass * 10;
		_acceleration.y += (_mass * 10 / FPS_LIMIT);
		if (_velocity.y > MINIMUM_VELOCITY_Y)
			_velocity.y -= (_velocity.y + _acceleration.y) / FPS_LIMIT;
		_sprite->setY(_sprite->getY() + (_velocity.y - GRAVITY) / FPS_LIMIT);

		//Updating X velocity
		if (_velocity.x >= STANDARD_VELOCITY_X || _velocity.x <= -STANDARD_VELOCITY_X)
			_sprite->setX(_sprite->getX() + _velocity.x / FPS_LIMIT);
		_velocity.x -= _velocity.x / FPS_LIMIT;
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

	void Character::setHealth(float _health)
	{
		this->_health = _health;
	}

	float	Character::getHealth() const
	{
		return (_health);
	}

	void Character::setGodMode(bool _godMode)
	{
		this->_godMode = _godMode;
	}

	void Character::toggleGodMode()
	{
		this->_godMode = !this->_godMode;
	}

	bool Character::isGodMode() const
	{
		return (this->_godMode);
	}

	void Character::changeHealth(float value)
	{
		this->setHealth(this->_health + value);
		this->_sprite->scale(Moo::Vector2f(value / 10, value / 10));
		this->_hitboxSprite->setScale(this->_sprite->getScale());
		this->resetHitbox();
	}

	void Character::checkEvaporation()
	{
		std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - _lastEvaporation;
		if (elapsed_seconds.count() > 4)
		{
			this->changeHealth(-EVAPORATION_RATE);
			std::cout << "Evaporating, player's health is now " << _health << std::endl;
			_lastEvaporation = std::chrono::system_clock::now();
		}
	}

	void Character::setTimers()
	{
		_startingTime = std::chrono::system_clock::now();
		_lastEvaporation = _startingTime;
	}
}