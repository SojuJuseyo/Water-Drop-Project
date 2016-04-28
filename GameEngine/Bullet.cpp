#include "Bullet.h"

namespace Moo
{
	Bullet::Bullet(Sprite *sprite, float mass, float health)
	{
		this->_sprite = sprite;
		this->setHitbox(sprite->getX(), sprite->getX() + sprite->getWidth(), sprite->getY(), sprite->getY() - (sprite->getHeight() / 3) * 2);
		this->setGravity(true);
		this->setVelocity(Vector2f(0, 0));
		this->_mass = mass;
		this->_health = health;
		this->_acceleration.y = this->_mass / FPS_LIMIT;
		this->_type = EntityType::BULLET;
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

	HitZone Bullet::collisionAABB(Entity *entity)
	{
		return (DynamicEntity::collisionAABB(entity));
	}
}
