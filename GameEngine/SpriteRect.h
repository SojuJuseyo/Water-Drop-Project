#pragma once

#include "d3d.h"

namespace Moo
{

	class SpriteRect
	{
	private:
		float _widthSprite; // la taille en largeur du sprite dans le jeu
		float _heightSprite; // la taille en hauteur du sprite dans le jeu
		float _widthTexture; // la taille en largeur d'une texture
		float _heightTexture; // la taille en hauteur d'une texture
		float _widthWholeTexture; // la taille en largeur de la texture complete
		float _heightWholeTexture; // la taille en hauteur de la texture complete
		XMFLOAT4 _color;

		float _offsetX;
		float _offsetY;

		VERTEX *_vertexTab;

	public:
		SpriteRect();
		SpriteRect(float, float, float, float, float, float, XMFLOAT4);
		~SpriteRect();

		VERTEX *makeVertexTab(int, int); // x et y
		VERTEX *getVertexTab();
	};

}