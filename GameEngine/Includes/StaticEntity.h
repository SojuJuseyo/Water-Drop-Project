#pragma once

#include "Vector2f.h"
#include "Entity.h"
#include "Sprite.h"

namespace Moo
{
	class StaticEntity : public Entity
	{
	public:
		StaticEntity(std::shared_ptr<Sprite>, EntityType, bool, bool);
		~StaticEntity();

		Sprite			*getSprite() const;
		Sprite			*getHitboxSprite() const;

		bool			getIsHeatZone() const;
		void			setIsHeatZone(bool);
		Hitbox			resetHitbox();

	private:
		std::shared_ptr<Sprite>			_sprite;
		std::shared_ptr<Sprite>			_hitboxSprite;
		std::shared_ptr<Texture>		_texture;

		bool		_isHeatZone;
	};
}
