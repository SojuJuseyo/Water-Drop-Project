#include "Texture.h"

namespace Moo
{
	Texture::Texture()
	{
		_texture = nullptr;
	}

	Texture::~Texture()
	{
		_texture->Release();
		_texture = nullptr;
	}

	void Texture::loadFromFile(const std::string &filename)
	{
		//D3DX11CreateShaderResourceViewFromFile(dev, filename.c_str(), NULL, NULL, &_texture, NULL);
	}

	ID3D11ShaderResourceView* Texture::getTexture()
	{
		return _texture;
	}
}