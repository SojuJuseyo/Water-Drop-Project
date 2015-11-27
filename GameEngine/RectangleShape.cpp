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

		_dev = d3d::getInstance().getD3DDevice();
		_devcon = d3d::getInstance().getContext();

		// load and compile the two shaders
		ID3D10Blob *VS, *PS;

		D3DX11CompileFromFile("shaders.shader", 0, 0, "VShader", "vs_4_0", 0, 0, 0, &VS, 0, 0);
		D3DX11CompileFromFile("shaders.shader", 0, 0, "PShader", "ps_4_0", 0, 0, 0, &PS, 0, 0);

		// encapsulate both shaders into shader objects
		_dev->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &pVS);
		_dev->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &pPS);

		// set the shader objects
		_devcon->VSSetShader(pVS, 0, 0);
		_devcon->PSSetShader(pPS, 0, 0);

		// create the input layout object
		D3D11_INPUT_ELEMENT_DESC ied[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		_dev->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);
		_devcon->IASetInputLayout(pLayout);
	}

	RectangleShape::~RectangleShape()
	{
		release();
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

	void RectangleShape::draw()
	{
		auto rect = CD3D11_RECT((LONG)_x, (LONG)_y, (LONG)_x + (LONG)_width, (LONG)_y + (LONG)_height);

		VERTEX _vertices[] =
		{
			{ Moo::d3d::PointToNdc(rect.left, rect.top, 0.0f), _color },
			{ Moo::d3d::PointToNdc(rect.right, rect.bottom, 0.0f), _color },
			{ Moo::d3d::PointToNdc(rect.left, rect.bottom, 0.0f), _color },

			{ Moo::d3d::PointToNdc(rect.left, rect.top, 0.0f), _color },
			{ Moo::d3d::PointToNdc(rect.right, rect.top, 0.0f), _color },
			{ Moo::d3d::PointToNdc(rect.right, rect.bottom, 0.0f), _color },
		};
		// create the vertex buffer
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));

		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(VERTEX) / sizeof(_vertices);
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		_dev->CreateBuffer(&bd, NULL, &_vertexBuffer);

		D3D11_MAPPED_SUBRESOURCE ms;
		_devcon->Map(_vertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
		memcpy(ms.pData, _vertices, sizeof(_vertices));
		_devcon->Unmap(_vertexBuffer, NULL);
	}

	ID3D11Buffer* const* RectangleShape::getVertexBuffer() const
	{ 
		return &_vertexBuffer;
	}
}