#include "Bullet.h"

namespace Moo
{
	Bullet::Bullet(Sprite *sprite, bool hasGravity)
	{
		this->_sprite = sprite;
		this->setHitbox(sprite->getX(), sprite->getX() + sprite->getWidth(), sprite->getY(), sprite->getY() - (sprite->getHeight() / 3) * 2);
		this->setGravity(hasGravity);
		_hitboxSprite = new Sprite(*_sprite);
		_texture = new Moo::Texture;
		_texture->loadFromFile("hitbox.dds");
		_hitboxSprite->loadTexture(_texture);
	}

	Bullet::~Bullet()
	{
		if (_sprite != nullptr)
			delete _sprite;
		if (_hitboxSprite != nullptr)
			delete _hitboxSprite;
		if (_texture != nullptr)
			_texture->release();
	}

	void Bullet::move(Direction _direction)
	{
		if (_direction == Direction::RIGHT)
		{
			_sprite->move(5, 0);
		}
	}

	Hitbox Bullet::resetHitbox()
	{
		_hitbox.x1 = this->_sprite->getX();
		_hitbox.y1 = this->_sprite->getY();
		_hitbox.x2 = this->_sprite->getX() + this->_sprite->getWidth();
		_hitbox.y2 = this->_sprite->getY() - (this->_sprite->getHeight() / 3) * 2;

		return _hitbox;
	}

	HitZone Bullet::collisionAABB(Entity *entity)
	{
		this->resetHitbox();
		return (Entity::collisionAABB(entity));
	}

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
