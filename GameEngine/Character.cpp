#include "Character.h"

namespace Moo
{
	Character::Character(Vector2f velocity, float mass, RectangleShape *sprite)
	{
		this->setVelocity(velocity);
		this->setMass(mass);
		this->_sprite = sprite;
		this->setHitbox(sprite->getX(), sprite->getX() + sprite->getWidth(), sprite->getY(), sprite->getY() + sprite->getHeight());
		this->_acceleration.y = this->_mass / FPS_LIMIT;
		_multiplier = 1;
	}

	Character::~Character()
	{
	}

	void	Character::move(Direction direction)
	{
		if (direction == LEFT)
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
			this->setVelocity(Moo::Vector2f(1, JUMP_VELOCITY));
	}

	void	Character::update()
	{
		//std::cout << "Y: " << _sprite->getY() << " && Velocity.y: " << _velocity.y << " && Acceleration: " << _acceleration.y << " && Multiplier: " << _multiplier << std::endl;
		if (_sprite->getY() <= (WINDOW_HEIGHT - _sprite->getHeight()) && _velocity.y != 0)
		{
			if (_velocity.y > 0 && _velocity.y < GRAVITY && _multiplier < 10)
			{
				_acceleration.y = _mass;
				++_multiplier;
			}
			_acceleration.y += (_mass / FPS_LIMIT) * _multiplier;
			_velocity.y -= (_velocity.y + _acceleration.y) / FPS_LIMIT;
			_sprite->setY(_sprite->getY() - (_velocity.y - GRAVITY) / FPS_LIMIT);
		}
		else if (_sprite->getY() > (WINDOW_HEIGHT - _sprite->getHeight()))
		{
			_velocity.y = 0;
			_acceleration.y = _mass;
			_multiplier = 1;
			_sprite->setY(WINDOW_HEIGHT - _sprite->getHeight());
		}
	}
}