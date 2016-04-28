#include "../Includes/StaticEntity.h"

namespace Moo
{
	StaticEntity::StaticEntity(std::shared_ptr<Sprite> sprite, EntityType type)
	{
		this->_sprite = sprite;
		this->setHitbox(sprite->getX(), sprite->getY() + sprite->getHeight(), sprite->getX() + sprite->getWidth(), sprite->getY());//x1 y1 x2 y2
		this->_type = type;
		_hitboxSprite = std::make_shared<Sprite>(*sprite);
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
}