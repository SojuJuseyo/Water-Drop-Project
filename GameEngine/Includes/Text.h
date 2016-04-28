#pragma once

#include "Texture.h"
#include "Drawable.h"
#include "Transformable.h"

namespace Moo
{
	__declspec(align(16)) class Text : public Drawable, public Transformable
	{
	public:
		Text(const std::string &text, float width, float height, float x, float y);
		Text(Text &Text);
		~Text();

		void* operator new(size_t i)
		{
			return _mm_malloc(i,16);
		}

			void operator delete(void* p)
		{
			_mm_free(p);
		}

		bool CompileD3DShader(char * filePath, char * entry, char * shaderModel, ID3DBlob ** buffer);

		void loadTexture();
		void createVertex(char letter, int offsetx);
		void draw();
		void setText(const std::string & text);
		float getWidth();
		float getHeight();
		ID3D11Buffer * const * getVertexBuffer() const;

		void release();

	private:
		std::string _text;
		Texture *_texture;
		VERTEX _vertices;
		float _width;
		float _height;
		XMFLOAT4 _color;
		ID3D11ShaderResourceView *_shaderRessource;
		ID3D11SamplerState* colorMapSampler;
		ID3D11BlendState* alphaBlendState;
		ID3D11Device *_dev;
		ID3D11DeviceContext *_devcon;

		ID3D11VertexShader* solidColorVS;
		ID3D11PixelShader* solidColorPS;

		ID3D11InputLayout* inputLayout;
		ID3D11Buffer* vertexBuffer;

		ID3D11ShaderResourceView* colorMap;


		ID3D11Buffer* colorCB;

		ID3D11Buffer* mvpCB;
		XMMATRIX vpMatrix;

	};
}