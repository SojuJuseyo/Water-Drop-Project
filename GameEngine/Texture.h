#pragma once

#include <string>

#include "d3d.h"

namespace Moo
{
	class Texture
	{
	public:
		Texture();
		~Texture();
		void loadFromFile(const std::string &filename);
		ID3D11ShaderResourceView* getTexture();
	private:
		ID3D11ShaderResourceView* _texture;
	};
}