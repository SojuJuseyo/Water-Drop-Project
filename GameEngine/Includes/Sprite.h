#pragma once

#include "Includes/Texture.h"
#include "Includes/Drawable.h"
#include "Includes/Transformable.h"
#include "Includes/SpriteRect.h"

using namespace Microsoft::WRL;

struct VertexPos
{
	XMFLOAT3 pos;
	XMFLOAT2 tex0;
};

namespace Moo
{
	__declspec(align(16)) class Sprite : public Drawable, public Transformable
	{
	public:
		Sprite(float width, float height, float x, float y);
		Sprite(Sprite &sprite);
		~Sprite();

		void* operator new(size_t i)
		{
			return _mm_malloc(i,16);
		}

			void operator delete(void* p)
		{
			_mm_free(p);
		}

		void loadTexture(Texture *);
		void loadTexture(Texture *, SpriteRect *);
		SpriteRect *getspriteRect();
		void draw();
		float getWidth();
		float getHeight();
		ID3D11Buffer * const * getVertexBuffer() const;

	private:
		Texture *_texture;
		float _width;
		float _height;
		ComPtr<ID3D11Device> _dev;
		ComPtr<ID3D11DeviceContext> _devcon;
		ComPtr<ID3D11Buffer> vertexBuffer;
		XMMATRIX vpMatrix;

		SpriteRect *_spriteRect;
	};
}