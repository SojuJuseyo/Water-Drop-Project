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

	HitZone Bullet::collisionAABB(Entity *entity)
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

	Hitbox Bullet::resetHitbox()
	{
		_hitbox.x1 = this->_sprite->getX();
		_hitbox.y1 = this->_sprite->getY();
		_hitbox.x2 = this->_sprite->getX() + this->_sprite->getWidth();
		_hitbox.y2 = this->_sprite->getY() - (this->_sprite->getHeight() / 3) * 2;

		return _hitbox;
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
