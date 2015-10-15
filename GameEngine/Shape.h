#pragma once

#include "d3d.h"

namespace Moo
{
	class Shape
	{
	public:
		Shape();
		virtual ~Shape() {}
		virtual void move(int x, int y) = 0;
		virtual int getX() = 0;
		virtual int getY() = 0;
		virtual void release() = 0;
		virtual void draw(ID3D11Device *dev, ID3D11DeviceContext *devcon) = 0;
		virtual ID3D11Buffer* const* getVertexBuffer() const = 0;
	};
}