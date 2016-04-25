#pragma once

#include "d3d.h"

namespace Moo
{

	class SpriteRect
	{
	private:
		float _widthSprite;
		float _heightSprite;
		float _widthTexture;
		float _heightTexture;
		float _widthWholeTexture;
		float _heightWholeTexture;

		float _offsetX;
		float _offsetY;

		VERTEX *_vertexTab;

	public:
		SpriteRect();
		SpriteRect(float, float, float, float, float, float);
		~SpriteRect();

		VERTEX *makeVertexTab(int, int); // x et y
		VERTEX *getVertexTab();
	};

}