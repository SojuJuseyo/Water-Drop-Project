#pragma once

#include <string>

#include "d3d.h"
#include "Drawable.h"
#include "Transformable.h"

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
		ID3D11Buffer * getVertexBuffer();
		ID3D11Buffer * getContentBuffer();
		void release();

	private:
		ID3D11Device *_dev;
		ID3D11DeviceContext *_devcon;

		ID3D11VertexShader* solidColorVS;
		ID3D11PixelShader* solidColorPS;

		ID3D11InputLayout* inputLayout;
		ID3D11Buffer* vertexBuffer;
		ID3D11Buffer* mvpCB;
		ID3D11SamplerState* colorMapSampler;
		ID3D11BlendState* alphaBlendState;
		ID3D11ShaderResourceView* colorMap;

		float _width;
		float _height;
		XMFLOAT4 _color;
	};
}