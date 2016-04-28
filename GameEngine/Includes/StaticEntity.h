#pragma once

#include "Includes/Vector2f.h"
#include "Includes/Entity.h"
#include "Includes/Sprite.h"

namespace Moo
{
	class StaticEntity : public Entity
	{
	public:
		StaticEntity(std::shared_ptr<Sprite>, EntityType);
		~StaticEntity();

		Sprite			*getSprite() const;
		Sprite			*getHitboxSprite() const;

	private:
		std::shared_ptr<Sprite>			_sprite;
		std::shared_ptr<Sprite>			_hitboxSprite;
		std::shared_ptr<Texture>		_texture;
	};
}
