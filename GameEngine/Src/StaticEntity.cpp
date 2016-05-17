#include "StaticEntity.h"

namespace Moo
{
	StaticEntity::StaticEntity(std::shared_ptr<Sprite> sprite, EntityType type, bool isHeatZone, bool isCollidable)
	{
		this->_sprite = sprite;
		this->setHitbox(sprite->getX(), sprite->getY() + sprite->getHeight(), sprite->getX() + sprite->getWidth(), sprite->getY());//x1 y1 x2 y2
		this->_type = type;
		this->_isHeatZone = isHeatZone;
		this->_isCollidable = isCollidable;
		_hitboxSprite = std::make_shared<Sprite>(sprite->getWidth(), sprite->getHeight(), sprite->getPosition().x, sprite->getPosition().y);
		_texture = std::make_shared<Moo::Texture>();
		_texture->loadFromFile(GRAPHICS_PATH + std::string("hitbox.dds"));
		_hitboxSprite->loadTexture(_texture.get());
	}

	StaticEntity::~StaticEntity()
	{
	}

	Sprite	*StaticEntity::getSprite() const
	{
		return _sprite.get();
	}

	Sprite	*StaticEntity::getHitboxSprite() const
	{
		_hitboxSprite->setPosition(_hitbox.x1, _hitbox.y2);

		return _hitboxSprite.get();
	}

	bool	StaticEntity::getIsHeatZone() const
	{
		return _isHeatZone;
	}

	void	StaticEntity::setIsHeatZone(bool isHeatZone)
	{
		this->_isHeatZone = isHeatZone;
	}

	Hitbox StaticEntity::resetHitbox()
	{
		_hitbox.x1 = this->_sprite->getX();
		_hitbox.y1 = this->_sprite->getY() + this->_sprite->getHeight();

		_hitbox.x2 = this->_sprite->getX() + this->_sprite->getWidth();
		_hitbox.y2 = this->_sprite->getY();

		return _hitbox;
	}
}