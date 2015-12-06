#pragma once

#include "WindowSettings.h"
#include "Vector2f.h"
#include "Entity.h"
#include "Sprite.h"

enum Direction
{
	LEFT,
	RIGHT
};

enum HitZone
{
	TOP,
	BOTTOM,
	LEFT_SIDE,
	RIGHT_SIDE,
	NONE
};

namespace Moo
{
	class Character : public Entity
	{
	public:
		Character(Vector2f, float, Sprite *, bool);
		virtual ~Character();
		void	move(Direction);
		void	jump();
		void	update();
		void	resetPos();
		Hitbox  resetHitbox();
		HitZone	collisionAABB(Entity *entity);
		Sprite	*getSprite() const;
		Sprite  *getHitboxSprite() const;
		void	setHealth(int);
		int		getHealth() const;

	private:
		Sprite *_sprite;
		Sprite *_hitboxSprite;

		// Health points
		int		_health;
	};
}