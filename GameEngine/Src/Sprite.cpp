#include "Sprite.h"

namespace Moo
{
	Sprite::Sprite(float width, float height, float x, float y)
	{
		_width = width;
		_height = height;
		setPosition(x, y);

		_dev = d3d::getInstance().getD3DDevice();
		_devcon = d3d::getInstance().getContext();
		_rect = nullptr;
		_texture = new Texture();
	}

	Sprite::Sprite(Sprite & sprite)
	{
		*this = sprite;
	}

	Sprite::~Sprite()
	{
	}

	void	Sprite::loadTexture(Texture *texture)
	{
		_texture = texture;
	}

	void	Sprite::setRectFromSpriteSheet(Vector2f pos, Vector2f size)
	{
		if (_rect == nullptr) {
			_rect = new VERTEX[6];
		}
		auto widthTexture = size.x;
		auto heightTexture = size.y;
		auto widthWholeTexture = _texture->getWidth();
		auto heightWholeTexture = _texture->getHeight();
		auto offsetX = widthTexture / widthWholeTexture;
		auto offsetY = heightTexture / heightWholeTexture;

		auto x = pos.x;
		auto y = pos.y;

		auto widthSprite = 0.5f;
		auto heightSprite = 0.5f;

		_rect[0].position = XMFLOAT3(widthSprite, heightSprite, 1.0f);
		_rect[0].texture = XMFLOAT2(offsetX * (x + 1), offsetY * y);

		_rect[1].position = XMFLOAT3(widthSprite, -heightSprite, 1.0f);
		_rect[1].texture = XMFLOAT2(offsetX * (x + 1), offsetY * (y + 1));

		_rect[2].position = XMFLOAT3(-widthSprite, -heightSprite, 1.0f);
		_rect[2].texture = XMFLOAT2(offsetX * x, offsetY * (y + 1));

		_rect[3].position = XMFLOAT3(-widthSprite, -heightSprite, 1.0f);
		_rect[3].texture = XMFLOAT2(offsetX * x, offsetY * (y + 1));

		_rect[4].position = XMFLOAT3(-widthSprite, heightSprite, 1.0f);
		_rect[4].texture = XMFLOAT2(offsetX * x, offsetY * y);

		_rect[5].position = XMFLOAT3(widthSprite, heightSprite, 1.0f);
		_rect[5].texture = XMFLOAT2(offsetX * (x + 1), offsetY * y);
	}

	void	Sprite::setResourceData()
	{
		D3D11_BUFFER_DESC vertexDesc;
		ZeroMemory(&vertexDesc, sizeof(vertexDesc));
		vertexDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexDesc.ByteWidth = sizeof(VERTEX) * 6;

		ZeroMemory(&_resourceData, sizeof(_resourceData));
		_resourceData.pSysMem = _rect;
		_dev->CreateBuffer(&vertexDesc, &_resourceData, &_vertexBuffer);
	}

	void	Sprite::draw()
	{
		if (_rect == nullptr) {
			this->setRectFromSpriteSheet(Moo::Vector2f(0, 0), Moo::Vector2f(_texture->getWidth(), _texture->getHeight()));
		}
		this->setResourceData();
		if (_texture == nullptr) {
			std::cout << "Texture null, call loadTexture before draw" << std::endl;
			return;
		}
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

		_vpMatrix = DirectX::XMMatrixMultiply((XMMATRIX)view, (XMMATRIX)projection);

		auto colorMap = _texture->getColorMap();
		_devcon->PSSetShaderResources(0, 1, &colorMap);
		auto vertexBuffer = _vertexBuffer.Get();
		_devcon->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		XMVECTOR axis = DirectX::XMVectorSet(0, 0, 0, 0);

		XMMATRIX translation = DirectX::XMMatrixTranslation(getPosition().x + (_width * getScale().x / 2), getPosition().y + (_height * getScale().y / 2), 0.5f);

		XMMATRIX rotationZ = XMMatrixRotationZ(DirectX::XMConvertToRadians(getRotation()));

		XMMATRIX scalling = DirectX::XMMatrixScaling(getScale().x * _width, getScale().y * _height, 1);

		XMMATRIX world = scalling * rotationZ * translation;

		XMMATRIX mvp = DirectX::XMMatrixMultiply((XMMATRIX)world, (XMMATRIX)_vpMatrix);
		mvp = DirectX::XMMatrixTranspose(mvp);

		auto contentBuffer = _texture->getContentBuffer();
		_devcon->UpdateSubresource(contentBuffer, 0, 0, &mvp, 0, 0);
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
		return _vertexBuffer.GetAddressOf();
	}

	Texture *Sprite::getTexture() const
	{
		return _texture;
	}
}