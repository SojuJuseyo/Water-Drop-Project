#pragma once

#include "WindowSettings.h"
#include "Vector2f.h"
#include "Entity.h"
#include "Sprite.h"

namespace Moo
{
	class Bullet : public Entity
	{
	public:
		Bullet(Sprite *, bool);
		virtual ~Bullet();
		void	move(Direction);
		Hitbox  resetHitbox();
		HitZone	collisionAABB(Entity *entity);
		Sprite	*getSprite() const;
		Sprite  *getHitboxSprite() const;

	private:
		Sprite *_sprite;
		Sprite *_hitboxSprite;
	};
}