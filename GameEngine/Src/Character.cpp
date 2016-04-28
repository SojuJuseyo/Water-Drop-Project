#include "../Includes/Character.h"

namespace Moo
{
	Character::Character(Vector2f velocity, float mass, std::shared_ptr<Sprite> sprite, bool hasGravity, float health, EntityType type)
	{
		this->_sprite = sprite;
		this->setHitbox(sprite->getX(), sprite->getY() + sprite->getHeight(), sprite->getX() + sprite->getWidth(), sprite->getY());//x1 y1 x2 y2
		_hitboxSprite = std::make_shared<Sprite>(*sprite);
		_texture = std::make_shared<Moo::Texture>();
		_texture->loadFromFile(GRAPHICS_PATH + std::string("hitbox.dds"));
		_hitboxSprite->loadTexture(_texture.get());

		this->_health = health;
		this->_type = type;
		this->_godMode = false;

		this->setVelocity(velocity);
		this->setMass(mass);
		this->setGravity(hasGravity);
		this->_acceleration.y = this->_mass / FPS_LIMIT;

		_characterVelocity = Vector2f(STANDARD_VELOCITY_X, 0);
	}

	Character::~Character()
	{
	}

	HitZone		Character::collisionAABB(Entity *entity)
	{
		return (DynamicEntity::collisionAABB(entity));
	}

	void	Character::move(Direction direction)
	{
		if ((this->getVelocity().x <= _characterVelocity.x && this->getVelocity().x >= -_characterVelocity.x) || this->getVelocity().y < 0)
		{
			if (direction == Direction::LEFT)
				this->setVelocity(Vector2f(-_characterVelocity.x, this->getVelocity().y));
			else
				this->setVelocity(Vector2f(_characterVelocity.x, this->getVelocity().y));
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
		if (_velocity.x >= _characterVelocity.x || _velocity.x <= -_characterVelocity.x)
			_sprite->setX(_sprite->getX() + _velocity.x / FPS_LIMIT);
		_velocity.x -= _velocity.x / FPS_LIMIT;
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
		if (this->_type == EntityType::PLAYER)
			this->_characterVelocity.x -= value;
	}

	void Character::checkEvaporation()
	{
		std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - this->_lastEvaporation;
		if (elapsed_seconds.count() > 4)
		{
			this->changeHealth(-EVAPORATION_RATE);
			this->_characterVelocity.x += EVAPORATION_RATE;
			std::cout << "Evaporating, player's health is now " << _health << std::endl;
			this->_lastEvaporation = std::chrono::system_clock::now();
		}
	}

	void Character::setWallJumpVelocity(bool positive)
	{
		if (positive == true)
			this->setVelocity(Vector2f(this->_characterVelocity.x * 2, this->getVelocity().y));
		else
			this->setVelocity(Vector2f(-this->_characterVelocity.x * 2, this->getVelocity().y));
	}

	void Character::setTimers()
	{
		this->_startingTime = std::chrono::system_clock::now();
		this->_lastEvaporation = this->_startingTime;
	}
}