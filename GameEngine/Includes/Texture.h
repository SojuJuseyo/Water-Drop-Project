#pragma once

#include <string>

#include "d3d.h"
#include "Drawable.h"
#include "Transformable.h"

#define GRAPHICS_PATH "Ressources/Graphics/"
using namespace Microsoft::WRL;

namespace Moo
{
	class Texture
	{
	public:
		Texture();
		~Texture();
		bool CompileD3DShader(char * filePath, char * entry, char * shaderModel, ID3DBlob ** buffer);
		void loadFromFile(const std::string &filename);

		ID3D11InputLayout * getInputLayout();
		ID3D11VertexShader * getVertexShader();
		ID3D11PixelShader * getPixelShader();
		ID3D11SamplerState * getColorMapSampler();
		ID3D11ShaderResourceView * getColorMap();
		ID3D11Buffer * getContentBuffer();
		float getWidth();
		float getHeight();
		void release();

		float _textureWidth;
		float _textureHeight;
	private:
		ComPtr<ID3D11Device> _dev;
		ComPtr<ID3D11DeviceContext> _devcon;

		ComPtr<ID3D11VertexShader> solidColorVS;
		ComPtr<ID3D11PixelShader> solidColorPS;

		ComPtr<ID3D11InputLayout> inputLayout;
		ComPtr<ID3D11Buffer> mvpCB;
		ComPtr<ID3D11SamplerState> colorMapSampler;
		ComPtr<ID3D11BlendState> alphaBlendState;
		ComPtr<ID3D11ShaderResourceView> colorMap;
	};
}