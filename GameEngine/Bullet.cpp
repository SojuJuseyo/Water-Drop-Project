#include "Bullet.h"

namespace Moo
{
	Bullet::Bullet(Sprite *sprite, bool hasGravity)
	{
		this->_sprite = sprite;
		this->setHitbox(sprite->getX(), sprite->getX() + sprite->getWidth(), sprite->getY(), sprite->getY() - (sprite->getHeight() / 3) * 2);
		this->setGravity(hasGravity);
		_hitboxSprite = new Sprite(*_sprite);
		Moo::Texture *hitbox = new Moo::Texture;
		hitbox->loadFromFile("hitbox.dds");
		_hitboxSprite->loadTexture(hitbox);
	}

	Bullet::~Bullet()
	{
	}

	void Bullet::move(Direction _direction)
	{
		if (_direction == Direction::RIGHT)
		{
			_sprite->move(5, 0);
		}
	}

	/*
	Hitbox Bullet::resetHitbox()
	{
		return Hitbox();
	}

	HitZone Bullet::collisionAABB(Entity * entity)
	{
		return HitZone();
	}*/

	Sprite *Bullet::getSprite() const
	{
		return _sprite;
	}

	Sprite *Bullet::getHitboxSprite() const
	{
		_hitboxSprite->setPosition(_hitbox.x1, _hitbox.y1);

		return _hitboxSprite;
	}
}
