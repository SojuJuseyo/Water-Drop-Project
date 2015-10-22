#pragma once

#include "Shape.h"

namespace Moo
{
	class RectangleShape : public Shape
	{
	public:
		RectangleShape(float width, float height, float x, float y, XMFLOAT4 color);
		~RectangleShape();
		void move(float x, float y);
		void setX(float x);
		void setY(float y);
		float getX();
		float getY();
		float getWidth();
		float getHeight();
		void release();
		void draw(ID3D11Device *dev, ID3D11DeviceContext *devcon);
		ID3D11Buffer* const* getVertexBuffer() const;
	private:
		ID3D11Buffer* _vertexBuffer;
		VERTEX _vertices;
		float _width;
		float _height;
		float _x;
		float _y;
		XMFLOAT4 _color;
	};
}