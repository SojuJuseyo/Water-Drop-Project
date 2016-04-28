#pragma once

#include "Vector2f.h"
#include "Entity.h"
#include "Sprite.h"

namespace Moo
{
	class StaticEntity : public Entity
	{
	public:
		StaticEntity(Sprite *, EntityType);
		~StaticEntity();

		Sprite			*getSprite() const;
		Sprite			*getHitboxSprite() const;

	private:
		Sprite			*_sprite;
		Sprite			*_hitboxSprite;
		Moo::Texture	*_texture;
	};
}
