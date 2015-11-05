#pragma once

#include "WindowSettings.h"
#include "RectangleShape.h"
#include "Vector2f.h"
#include "Entity.h"

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
		Character(Vector2f, float, RectangleShape *, bool);
		virtual ~Character();
		void	move(Direction);
		void	jump();
		void	update();
		void	resetPos();
		Hitbox  resetHitbox();
		HitZone	collisionAABB(Entity *entity);
		RectangleShape	*getSprite() const;

	private:
		RectangleShape *_sprite;
		unsigned short	_multiplier;
	};
}