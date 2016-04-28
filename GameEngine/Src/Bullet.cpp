#include "Includes/Bullet.h"

namespace Moo
{
	Bullet::Bullet(std::shared_ptr<Sprite> sprite, float mass, float health)
	{
		this->_sprite = sprite;
		this->setHitbox(sprite->getX(), sprite->getX() + sprite->getWidth(), sprite->getY(), sprite->getY() - (sprite->getHeight() / 3) * 2);
		this->setGravity(true);
		this->setVelocity(Vector2f(0, 0));
		this->_mass = mass;
		this->_health = health;
		this->_acceleration.y = this->_mass / FPS_LIMIT;
		this->_type = EntityType::BULLET;
		_hitboxSprite = std::make_shared<Sprite>(*sprite);
		_texture = std::make_shared<Moo::Texture>();
		_texture->loadFromFile(GRAPHICS_PATH + std::string("hitbox.dds"));
		_hitboxSprite->loadTexture(_texture.get());
	}

	Bullet::~Bullet()
	{
	}

	HitZone Bullet::collisionAABB(Entity *entity)
	{
		return (DynamicEntity::collisionAABB(entity));
	}
}
