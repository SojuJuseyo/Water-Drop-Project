#include "StaticEntity.h"

namespace Moo
{
	StaticEntity::StaticEntity(Sprite *sprite, EntityType type)
	{
		this->_sprite = sprite;
		this->setHitbox(sprite->getX(), sprite->getY() + sprite->getHeight(), sprite->getX() + sprite->getWidth(), sprite->getY());//x1 y1 x2 y2
		this->_type = type;
		_hitboxSprite = new Sprite(*_sprite);
		_texture = new Moo::Texture;
		_texture->loadFromFile("hitbox.dds");
		_hitboxSprite->loadTexture(_texture);
	}


	StaticEntity::~StaticEntity()
	{
		if (_sprite != nullptr)
			delete _sprite;
		if (_hitboxSprite != nullptr)
			delete _hitboxSprite;
		if (_texture != nullptr)
			_texture->release();
	}


	Sprite	*StaticEntity::getSprite() const
	{
		return _sprite;
	}

	Sprite	*StaticEntity::getHitboxSprite() const
	{
		_hitboxSprite->setPosition(_hitbox.x1, _hitbox.y2);

		return _hitboxSprite;
	}
}