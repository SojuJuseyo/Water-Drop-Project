#include "Character.h"

namespace Moo
{
	Character::Character(Vector2f velocity, float mass, std::shared_ptr<Sprite> sprite, bool hasGravity, float health, EntityType type, Direction direction)
	{
		this->_sprite = sprite;
		this->setHitbox(sprite->getX(), sprite->getY() + sprite->getHeight(), sprite->getX() + sprite->getWidth(), sprite->getY());//x1 y1 x2 y2
		_hitboxSprite = std::make_shared<Sprite>(sprite->getWidth(), sprite->getHeight(), sprite->getPosition().x, sprite->getPosition().y);
		_texture = std::make_shared<Moo::Texture>();
		_texture->loadFromFile(GRAPHICS_PATH + std::string("hitbox.dds"));
		_hitboxSprite->loadTexture(_texture.get());
		//_hitboxSprite->setRectFromSpriteSheet(Moo::Vector2f(0, 0), Moo::Vector2f(100, 100));
		this->_health = health;
		this->_type = type;
		this->_godMode = false;
		this->_direction = direction;

		this->setVelocity(velocity);
		this->setMass(mass);
		this->setGravity(hasGravity);
		this->_acceleration.y = this->_mass / FPS_LIMIT;
		_defaultVelocity = 666;
		_isJumping = false;

		//Save variables
		_oldVelocity = this->_velocity;
		_oldMass = this->_mass;
		_oldHealth = this->_health;
		_oldAcceleration = this->_acceleration;
		_oldHasGravity = this->_hasGravity;
		_oldDirection = this->_direction;
		_oldHitbox = this->_hitbox;
		_oldSpritePosition = this->_sprite->getPosition();
		_oldSpriteScale = this->_sprite->getScale();
		_oldHitboxSpritePosition = this->_hitboxSprite->getPosition();
		_oldHitboxSpriteScale = this->_hitboxSprite->getScale();
	}

	Character::~Character()
	{
	}

	void		Character::reset()
	{
		this->_velocity = _oldVelocity;
		this->_mass = _oldMass;
		this->_health = _oldHealth;
		this->_acceleration = _oldAcceleration;
		this->_hasGravity = _oldHasGravity;
		this->_direction = _oldDirection;
		this->_hitbox = _oldHitbox;
		this->_sprite->setPosition(_oldSpritePosition);
		this->_sprite->setScale(_oldSpriteScale);
		this->_hitboxSprite->setPosition(_oldHitboxSpritePosition);
		this->_hitboxSprite->setScale(_oldHitboxSpriteScale);
		this->_isActivated = true;
		this->_godMode = false;
		this->resetHitbox();
	}

	HitZone		Character::collisionAABB(Entity *entity)
	{
		return (DynamicEntity::collisionAABB(entity));
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
		/*else
			std::cout << "Wait your velocity X is: " << this->getVelocity().x << std::endl;*/
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

	float tmp = 0;

	void	Character::update()
	{
		//Updating Y velocity
		if (_velocity.y > 0 && _velocity.y < GRAVITY)
		{
			_acceleration.y = _mass * 10;
		}
		_acceleration.y += (_mass * 10 / FPS_LIMIT);
		if (_velocity.y > MINIMUM_VELOCITY_Y)
		{
			_velocity.y -= (_velocity.y + _acceleration.y) / FPS_LIMIT;
			if (_defaultVelocity == 666)
			{
				_defaultVelocity = _velocity.y;
			}
		}
		_sprite->setY(_sprite->getY() + (_velocity.y - GRAVITY) / FPS_LIMIT);

		//Updating X velocity
		if (_velocity.x >= STANDARD_VELOCITY_X || _velocity.x <= -STANDARD_VELOCITY_X)
			_sprite->setX(_sprite->getX() + _velocity.x / FPS_LIMIT);
		_velocity.x -= _velocity.x / FPS_LIMIT;
		tmp = _velocity.y;
		if (_velocity.y > _defaultVelocity)
		{
			_isJumping = true;
			if (this->getDirection() == Direction::LEFT)
			{
				if (_velocity.y > 525)
					this->getSprite()->setRectFromSpriteSheet(Moo::Vector2f(1, 0), Moo::Vector2f(36, 42));
				if (_velocity.y < 525 && _velocity.y > 350)
					this->getSprite()->setRectFromSpriteSheet(Moo::Vector2f(2, 0), Moo::Vector2f(36, 42));
				if (_velocity.y < 175)
					this->getSprite()->setRectFromSpriteSheet(Moo::Vector2f(3, 0), Moo::Vector2f(36, 42));
			}
			else
			{
				if (_velocity.y > 525)
					this->getSprite()->setRectFromSpriteSheet(Moo::Vector2f(1, 1), Moo::Vector2f(36, 42));
				if (_velocity.y < 525 && _velocity.y > 350)
					this->getSprite()->setRectFromSpriteSheet(Moo::Vector2f(2, 1), Moo::Vector2f(36, 42));
				if (_velocity.y < 175)
					this->getSprite()->setRectFromSpriteSheet(Moo::Vector2f(3, 1), Moo::Vector2f(36, 42));
			}
		}
		if (_velocity.y < _defaultVelocity && _isJumping == true)
		{

			if (this->getDirection() == Direction::LEFT)
			{
				if (_velocity.y > -72)
					this->getSprite()->setRectFromSpriteSheet(Moo::Vector2f(2, 0), Moo::Vector2f(36, 42));
				if (_velocity.y < -72 && _velocity.y > -147)
					this->getSprite()->setRectFromSpriteSheet(Moo::Vector2f(1, 0), Moo::Vector2f(36, 42));
				if (_velocity.y < -219)
					this->getSprite()->setRectFromSpriteSheet(Moo::Vector2f(0, 0), Moo::Vector2f(36, 42));
			}
			else
			{
				if (_velocity.y > -72)
					this->getSprite()->setRectFromSpriteSheet(Moo::Vector2f(2, 1), Moo::Vector2f(36, 42));
				if (_velocity.y < -72 && _velocity.y > -147)
					this->getSprite()->setRectFromSpriteSheet(Moo::Vector2f(1, 1), Moo::Vector2f(36, 42));
				if (_velocity.y < -219)
					this->getSprite()->setRectFromSpriteSheet(Moo::Vector2f(0, 1), Moo::Vector2f(36, 42));
			}
		}
		if (_velocity.y == _defaultVelocity)
		{
			_isJumping = false;
			if (this->getDirection() == Direction::LEFT)
				this->getSprite()->setRectFromSpriteSheet(Moo::Vector2f(0, 0), Moo::Vector2f(36, 42));
			else
				this->getSprite()->setRectFromSpriteSheet(Moo::Vector2f(0, 1), Moo::Vector2f(36, 42));
		}
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

	void Character::checkEvaporation()
	{
		std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - this->_lastEvaporation;
		if (elapsed_seconds.count() > 4)
		{
			this->changeHealth(-EVAPORATION_RATE);
			std::cout << "Evaporating, player's health is now " << _health << std::endl;
			this->_lastEvaporation = std::chrono::system_clock::now();
		}
	}

	void Character::setWallJumpVelocity(bool positive)
	{
		if (positive == true)
			this->setVelocity(Vector2f(/*this->_characterVelocity.x * 2*/500, this->getVelocity().y + this->getVelocity().y > 0 ? 40.f : 70.f));
		else 
			this->setVelocity(Vector2f(/*-this->_characterVelocity.x * 2*/-500, this->getVelocity().y + this->getVelocity().y > 0 ? 40.f : 70.f));
	}

	void Character::setTimers()
	{
		this->_startingTime = std::chrono::system_clock::now();
		this->_lastEvaporation = this->_startingTime;
	}
}