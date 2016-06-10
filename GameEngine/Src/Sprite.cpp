#include "Sprite.h"

namespace Moo
{
	Sprite::Sprite(float width, float height, float x, float y)
	{
		_width = width;
		_height = height;
		_position.x = x;
		_position.y = y;

		_dev = d3d::getInstance().getD3DDevice();
		_devcon = d3d::getInstance().getContext();
		_rect = nullptr;
		_isAnimated = false;
	}

	Sprite::Sprite(float width, float height, float x, float y, int rows, int columns, bool looping, float framesPerSecond)
	{
		_width = width;
		_height = height;
		_position.x = x;
		_position.y = y;

		_dev = d3d::getInstance().getD3DDevice();
		_devcon = d3d::getInstance().getContext();
		_rect = nullptr;
		_rows = rows;
		_columns = columns;
		_isAnimated = true;
		_currentFrame = 0;
		_framesPerSecond = framesPerSecond;
		_looping = looping;
		_timer = nullptr;
		if (_looping)
			_launchAnim = true;
		else
			_launchAnim = false;
	}

	Sprite::~Sprite()
	{
	}

	void	Sprite::loadTexture(Texture *texture)
	{
		_texture = texture;
		if (_rect == nullptr)
			this->setRectFromSpriteSheet(Moo::Vector2f(0, 0), Moo::Vector2f(_texture->getWidth(), _texture->getHeight()));
	}

	void	Sprite::setRectFromSpriteSheet(Vector2f pos, Vector2f size)
	{
		if (_rect == nullptr) {
			_rect = new VERTEX[6];
		}
		float widthTexture = size.x;
		float heightTexture = size.y;
		float widthWholeTexture = _texture->getWidth();
		float heightWholeTexture = _texture->getHeight();
		float offsetX = widthTexture / widthWholeTexture;
		float offsetY = heightTexture / heightWholeTexture;

		float x = pos.x;
		float y = pos.y;

		float widthSprite = 0.5f;
		float heightSprite = 0.5f;

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

		this->setResourceData();
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
		DirectX::ThrowIfFailed(
			_dev->CreateBuffer(
				&vertexDesc,
				&_resourceData,
				&_vertexBuffer
				)
			);

		D3D11_BUFFER_DESC constDesc;
		ZeroMemory(&constDesc, sizeof(constDesc));
		constDesc.Usage = D3D11_USAGE_DEFAULT;
		constDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		constDesc.ByteWidth = sizeof(XMMATRIX);

		DirectX::ThrowIfFailed(
			_dev->CreateBuffer(
				&constDesc,
				0,
				&_constantBuffer
				)
			);

		transform();
	}

	void	Sprite::transform()
	{
		XMMATRIX view = d3d::getInstance().getView();
		XMMATRIX projection = d3d::getInstance().getProjection();

		_vpMatrix = DirectX::XMMatrixMultiply((XMMATRIX)view, (XMMATRIX)projection);

		XMVECTOR axis = DirectX::XMVectorSet(0, 0, 0, 0);

		XMMATRIX translation = DirectX::XMMatrixTranslation(getPosition().x + (_width * getScale().x / 2), getPosition().y + (_height * getScale().y / 2), 1.f);

		XMMATRIX rotationZ = XMMatrixRotationZ(DirectX::XMConvertToRadians(getRotation()));

		XMMATRIX scalling = DirectX::XMMatrixScaling(getScale().x * _width, getScale().y * _height, 1);

		XMMATRIX world = scalling * rotationZ * translation;

		XMMATRIX mvp = DirectX::XMMatrixMultiply((XMMATRIX)world, (XMMATRIX)_vpMatrix);
		mvp = DirectX::XMMatrixTranspose(mvp);
		_devcon->UpdateSubresource(_constantBuffer.Get(), 0, 0, &mvp, 0, 0);
	}

	void    Sprite::doAnimation()
	{
		_launchAnim = true;
	}

	void	Sprite::draw()
	{
		if (_isAnimated)
		{
			if (_launchAnim)
			{
				if (_framesPerSecond != -1)
				{
					if (_timer == nullptr)
						_timer = new Timer;
					if (_timer->getElapsedSeconds() > _framesPerSecond)
					{
						_currentFrame++;
						if (_currentFrame == _rows * _columns)
						{
							if (!_looping)
								_launchAnim = false;
							_currentFrame = 0;
						}
						this->setRectFromSpriteSheet(Moo::Vector2f(float(_currentFrame % _columns), float(_currentFrame / _columns)), Moo::Vector2f(_width, _height));
						_timer->reset();
					}
				}
				else
				{
					if (_currentFrame == _rows * _columns)
						_currentFrame = 0;
					this->setRectFromSpriteSheet(Moo::Vector2f(float(_currentFrame % _columns), float(_currentFrame / _columns)), Moo::Vector2f(_width, _height));
					_currentFrame++;
				}
			}
		}
		unsigned int stride = sizeof(VERTEX);
		unsigned int offset = 0;
		_devcon->IASetInputLayout(_texture->getInputLayout());
		_devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		_devcon->VSSetShader(_texture->getVertexShader(), 0, 0);
		_devcon->PSSetShader(_texture->getPixelShader(), 0, 0);

		auto colorMapSampler = _texture->getColorMapSampler();
		_devcon->PSSetSamplers(0, 1, &colorMapSampler);

		auto colorMap = _texture->getColorMap();
		_devcon->PSSetShaderResources(0, 1, &colorMap);
		_devcon->IASetVertexBuffers(0, 1, _vertexBuffer.GetAddressOf(), &stride, &offset);
		_devcon->VSSetConstantBuffers(0, 1, _constantBuffer.GetAddressOf());
		transform();
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