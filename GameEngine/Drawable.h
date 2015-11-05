#pragma once

namespace Moo
{
	class Drawable
	{
	public:
		Drawable();
		virtual ~Drawable() {}
		virtual void draw() = 0;
	};
}