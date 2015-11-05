#pragma once

#include "d3d.h"
#include "Drawable.h"
#include "Transformable.h"

namespace Moo
{
	class Shape : public Drawable, public Transformable
	{
	public:
		Shape();
		virtual ~Shape() {}
		virtual void draw() = 0;
		virtual ID3D11Buffer* const* getVertexBuffer() const = 0;
	};
}