#include "Sprite.h"

namespace Moo
{
	Sprite::Sprite(float width, float height, float x, float y) :
		solidColorVS(0), solidColorPS(0),
		inputLayout(0),
		colorMap(0), colorMapSampler(0),
		mvpCB(0), alphaBlendState(0)
	{
		_width = width;
		_height = height;
		setPosition(x, y);

		_dev = d3d::getInstance().getD3DDevice();
		_devcon = d3d::getInstance().getContext();
	}

	Sprite::Sprite(Sprite & sprite)
	{
		*this = sprite;
	}

	Sprite::~Sprite()
	{
		//delete(_texture);
	}

	void	Sprite::loadTexture(Texture *texture)
	{
		_texture = texture;
	}

	void	Sprite::draw()
	{	
		unsigned int stride = sizeof(VERTEX);
		unsigned int offset = 0;

		_devcon->IASetInputLayout(_texture->getInputLayout());
		_devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		_devcon->VSSetShader(_texture->getVertexShader(), 0, 0);
		_devcon->PSSetShader(_texture->getPixelShader(), 0, 0);
		auto colorMapSampler = _texture->getColorMapSampler();
		_devcon->PSSetSamplers(0, 1, &colorMapSampler);

		XMMATRIX view = d3d::getInstance().getView();
		XMMATRIX projection = d3d::getInstance().getProjection();

		vpMatrix = DirectX::XMMatrixMultiply((XMMATRIX)view, (XMMATRIX)projection);

		auto colorMap = _texture->getColorMap();
		_devcon->PSSetShaderResources(0, 1, &colorMap);
		auto vertexBuffer = _texture->getVertexBuffer();
		_devcon->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		XMVECTOR axis = DirectX::XMVectorSet(0, 0, 0, 0);

		XMMATRIX translation = DirectX::XMMatrixTranslation(getPosition().x + (_width * getScale().x / 2), getPosition().y + (_height * getScale().y / 2), 0.5f);
		XMMATRIX rotationZ = XMMatrixRotationZ(DirectX::XMConvertToRadians(getRotation()));

		XMMATRIX scalling = DirectX::XMMatrixScaling(getScale().x * (_width / 50), getScale().y * (_height / 50), 1);
		
		XMMATRIX world = scalling * rotationZ * translation;

		XMMATRIX mvp = DirectX::XMMatrixMultiply((XMMATRIX)world, (XMMATRIX)vpMatrix);
		mvp = DirectX::XMMatrixTranspose(mvp);

		_devcon->UpdateSubresource(_texture->getContentBuffer(), 0, 0, &mvp, 0, 0);
		auto contentBuffer = _texture->getContentBuffer();
		_devcon->VSSetConstantBuffers(0, 1, &contentBuffer);
		_devcon->Draw(6, 0);
	}

	float Sprite::getWidth()
	{
		return _width * getScale().x;
	}

	float Sprite::getHeight()
	{
		return _height * getScale().y;
	}

	ID3D11Buffer* const* Sprite::getVertexBuffer() const
	{
		return &vertexBuffer;
	}
}