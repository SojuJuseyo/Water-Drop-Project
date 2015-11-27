#pragma once

#include "WindowSettings.h"
#include "Vector2f.h"
#include "Entity.h"
#include "Sprite.h"
// For the enum Direction
#include "Character.h"

/*
enum HitZone
{
	TOP,
	BOTTOM,
	LEFT_SIDE,
	RIGHT_SIDE,
	NONE
};*/

namespace Moo
{
	class Bullet : public Entity
	{
	public:
		Bullet(Sprite *, bool);
		virtual ~Bullet();
		void	move(Direction);
		/*Hitbox  resetHitbox();
		HitZone	collisionAABB(Entity *entity);*/
		Sprite	*getSprite() const;
		Sprite  *getHitboxSprite() const;

	private:
		Sprite *_sprite;
		Sprite *_hitboxSprite;
	};
}