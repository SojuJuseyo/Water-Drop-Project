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

namespace Moo
{
	class Character : public Entity
	{
	public:
		Character(Vector2f, float, RectangleShape *);
		virtual ~Character();
		void	move(Direction);
		void	jump();
		void	update();

	private:
		RectangleShape *_sprite;
		unsigned short	_multiplier;
	};
}