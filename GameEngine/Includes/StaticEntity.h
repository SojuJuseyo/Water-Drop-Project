#pragma once

#include "../Includes/Vector2f.h"
#include "../Includes/Entity.h"
#include "../Includes/Sprite.h"

namespace Moo
{
	class StaticEntity : public Entity
	{
	public:
		StaticEntity(std::shared_ptr<Sprite>, EntityType, bool);
		~StaticEntity();

		Sprite			*getSprite() const;
		Sprite			*getHitboxSprite() const;
		bool			getIsHeatZone() const;

	private:
		std::shared_ptr<Sprite>			_sprite;
		std::shared_ptr<Sprite>			_hitboxSprite;
		std::shared_ptr<Texture>		_texture;

		bool		_isHeatZone;
	};
}
