#include "RectangleShape.h"

namespace Moo
{
	RectangleShape::RectangleShape(int width, int height, int x, int y, XMFLOAT4 color)
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

	void RectangleShape::move(int x, int y)
	{
		_x = x;
		_y = y;
	}
	
	int RectangleShape::getX()
	{
		return _x;
	}

	int RectangleShape::getY()
	{
		return _y;
	}

	int RectangleShape::getWidth()
	{
		return _width;
	}

	int RectangleShape::getHeight()
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

		bd.Usage = D3D11_USAGE_DYNAMIC;                // write access access by CPU and GPU
		bd.ByteWidth = sizeof(VERTEX) * sizeof(_vertices);             // size is the VERTEX struct * 3
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;       // use as a vertex buffer
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;    // allow CPU to write in buffer

		dev->CreateBuffer(&bd, NULL, &_vertexBuffer);       // create the buffer

		D3D11_MAPPED_SUBRESOURCE ms;
		devcon->Map(_vertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);    // map the buffer
		memcpy(ms.pData, _vertices, sizeof(_vertices));                 // copy the data
		devcon->Unmap(_vertexBuffer, NULL);                                      // unmap the buffer
	}

	ID3D11Buffer* const* RectangleShape::getVertexBuffer() const
	{ 
		return &_vertexBuffer;
	}
}