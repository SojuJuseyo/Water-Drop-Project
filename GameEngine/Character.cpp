#include "Character.h"

namespace Moo
{
	Character::Character(Vector2f velocity, float mass, RectangleShape *sprite)
	{
		this->setVelocity(velocity);
		this->setMass(mass);
		this->sprite = sprite;
		this->setHitbox(sprite->getX(), sprite->getX() + sprite->getWidth(), sprite->getY(), sprite->getY() + sprite->getHeight());
		_acceleration.y = _mass * 1 / 60;
	}

	Character::~Character()
	{
	}

	void	Character::move(Direction direction)
	{
		if (direction == LEFT)
		{
			sprite->move(-_velocity.x, 0);
		}
		else
		{
			sprite->move(_velocity.x, 0);
		}
	}

	void	Character::jump()
	{
		if (_velocity.y == 1)
		{
			this->setVelocity(Moo::Vector2f(0, 50)); 
			sprite->move(0, -_velocity.y);
		}
	}

	void	Character::update()
	{
		std::cout << "Y: " << sprite->getY() << " && Velocity: " << _acceleration.y << std::endl;
		if (sprite->getY() < 600 - sprite->getHeight())
		{
			sprite->setY(sprite->getY() + (_velocity.y + 5) / 60);
		}
		if (_velocity.y > 1) {
			_velocity.y -= (_velocity.y + _acceleration.y) * 1 / 60;
			_acceleration.y += _mass * 1 / 60;
		}
		else if (_velocity.y < 1) {
			_velocity.y = 1;
			_acceleration.y = 0;
		}
	}
}