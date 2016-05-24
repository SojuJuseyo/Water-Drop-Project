#pragma once

#include "Texture.h"
#include "Drawable.h"
#include "Transformable.h"
#include "Fps.h"

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
		Sprite() {}
		Sprite(float width, float height, float x, float y);
		Sprite(float width, float height, float x, float y, float framesPerSecond, int rows, int columns);
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
		void setResourceData();
		void transform();
		void setRectFromSpriteSheet(Vector2f pos, Vector2f size);
		void draw();
		float getWidth();
		float getHeight();
		ID3D11Buffer * const * getVertexBuffer() const;
		Texture * getTexture() const;

	private:
		Texture *_texture;
		float _width;
		float _height;
		ComPtr<ID3D11Device> _dev;
		ComPtr<ID3D11DeviceContext> _devcon;
		ComPtr<ID3D11Buffer> _vertexBuffer;
		ComPtr<ID3D11Buffer> _constantBuffer;
		XMMATRIX _vpMatrix;
		VERTEX *_rect;

		D3D11_SUBRESOURCE_DATA _resourceData;

		Timer *_timer;
		bool _isAnimated;
		float _framesPerSecond;
		int _rows;
		int _columns;
		int _currentFrame;
	};
}