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

namespace Moo
{
	class Character : public Entity
	{
	public:
		Character(Vector2f, float, Sprite *);

		virtual ~Character();
		void	move(Direction);
		void	jump();
		void	update();

	private:
		Sprite *_sprite;
		unsigned short	_multiplier;
	};
}