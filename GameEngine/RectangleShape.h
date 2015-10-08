#pragma once

#include "d3d.h"

namespace Moo
{
	class RectangleShape
	{
	public:
		RectangleShape(int width, int height, int x, int y, XMFLOAT4 color);
		~RectangleShape();
		void move(int x, int y);
		int getX();
		int getY();
		int getWidth();
		int getHeight();
		void release();
		void draw(ID3D11Device *dev, ID3D11DeviceContext *devcon);
		ID3D11Buffer* const* getVertexBuffer() const;
	private:
		ID3D11Buffer* _vertexBuffer;
		VERTEX _vertices;
		int _width;
		int _height;
		int _x;
		int _y;
		XMFLOAT4 _color;
	};
}