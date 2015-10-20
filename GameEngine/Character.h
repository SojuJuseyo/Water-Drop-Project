#pragma once

#include "RectangleShape.h"
#include "Entity.h"

namespace Moo
{
	class Character : public Entity
	{
	public:
		Character();
		virtual ~Character();

	private:
		RectangleShape *sprite;
	};
}