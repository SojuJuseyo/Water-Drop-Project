#include "RectangleShape.h"

namespace Moo
{
	RectangleShape::RectangleShape(float width, float height, float x, float y, XMFLOAT4 color)
	{
		ID3D11Buffer* _vertexBuffer = nullptr;
		_width = width;
		_height = height;
		_x = x;
		_y = y;
		_color = color;
	}

	RectangleShape::~RectangleShape()
	{
	}

	void RectangleShape::move(float x, float y)
	{
		_x += x;
		_y += y;
	}
	
	void RectangleShape::setX(float x)
	{
		_x = x;
	}

	void RectangleShape::setY(float y)
	{
		_y = y;
	}

	float RectangleShape::getX()
	{
		return _x;
	}

	float RectangleShape::getY()
	{
		return _y;
	}

	float RectangleShape::getWidth()
	{
		return _width;
	}

	float RectangleShape::getHeight()
	{
		return _height;
	}

	void RectangleShape::release()
	{
		_vertexBuffer->Release();
	}

	void RectangleShape::draw(ID3D11Device *dev, ID3D11DeviceContext *devcon)
	{
		auto rect = CD3D11_RECT(_x, _y, _x + _width, _y + _height);
		VERTEX _vertices[] =
		{
			{ Moo::d3d::PointToNdc(rect.left, rect.bottom, 0.0f), _color },
			{ Moo::d3d::PointToNdc(rect.left, rect.top, 0.0f), _color },
			{ Moo::d3d::PointToNdc(rect.right, rect.top, 0.0f), _color },
			{ Moo::d3d::PointToNdc(rect.left, rect.bottom, 0.0f), _color },
			{ Moo::d3d::PointToNdc(rect.right, rect.top, 0.0f), _color },
			{ Moo::d3d::PointToNdc(rect.right, rect.bottom, 0.0f), _color },
		};
		// create the vertex buffer
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));

		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(VERTEX) * sizeof(_vertices);
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		dev->CreateBuffer(&bd, NULL, &_vertexBuffer);

		D3D11_MAPPED_SUBRESOURCE ms;
		devcon->Map(_vertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
		memcpy(ms.pData, _vertices, sizeof(_vertices));
		devcon->Unmap(_vertexBuffer, NULL);
	}

	ID3D11Buffer* const* RectangleShape::getVertexBuffer() const
	{ 
		return &_vertexBuffer;
	}
}