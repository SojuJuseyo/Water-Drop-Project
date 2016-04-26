#include "SpriteRect.h"

namespace Moo
{
	SpriteRect::SpriteRect()
	{}

	SpriteRect::SpriteRect(
		float widthTexture,
		float heightTexture,
		float widthWholeTexture,
		float heightWholeTexture)
	{
		_widthSprite = 25.f; // la taille en largeur du sprite dans le jeu
		_heightSprite = 25.f; // la taille en hauteur du sprite dans le jeu
		_widthTexture = widthTexture; // la taille en largeur d'une texture
		_heightTexture = heightTexture; // la taille en hauteur d'une texture
		_widthWholeTexture = widthWholeTexture; // la taille en largeur de la texture complete
		_heightWholeTexture = heightWholeTexture; // la taille en hauteur de la texture complete
		_offsetX = widthTexture / widthWholeTexture; // Le pourcentage en x d'une texture dans la texture complete
		_offsetY = heightTexture / heightWholeTexture; // Le pourcentage en y d'une texture dans la texture complete
		_vertexTab = nullptr;
	}

	SpriteRect::~SpriteRect()
	{
		if (_vertexTab != nullptr)
			delete _vertexTab;
	}

	VERTEX *SpriteRect::makeVertexTab(int x, int y) // Créer un tableau de vertex pour la texture correspondant à l'emplacement du sprite désiré sur la texture en x et y
	{
		_vertexTab = new VERTEX[6];

		_vertexTab[0].position = XMFLOAT3(_widthSprite, _heightSprite, 1.0f);
		_vertexTab[0].texture = XMFLOAT2(_offsetX * (x + 1), _offsetY * y);

		_vertexTab[1].position = XMFLOAT3(_widthSprite, -_heightSprite, 1.0f);
		_vertexTab[1].texture = XMFLOAT2(_offsetX * (x + 1), _offsetY * (y + 1));

		_vertexTab[2].position = XMFLOAT3(-_widthSprite, -_heightSprite, 1.0f);
		_vertexTab[2].texture = XMFLOAT2(_offsetX * x, _offsetY * (y + 1));

		_vertexTab[3].position = XMFLOAT3(-_widthSprite, -_heightSprite, 1.0f);
		_vertexTab[3].texture = XMFLOAT2(_offsetX * x, _offsetY * (y + 1));

		_vertexTab[4].position = XMFLOAT3(-_widthSprite, _heightSprite, 1.0f);
		_vertexTab[4].texture = XMFLOAT2(_offsetX * x, _offsetY * y);

		_vertexTab[5].position = XMFLOAT3(_widthSprite, _heightSprite, 1.0f);
		_vertexTab[5].texture = XMFLOAT2(_offsetX * (x + 1), _offsetY * y);

		return _vertexTab;
	}

	VERTEX *SpriteRect::getVertexTab()
	{
		return _vertexTab;
	}
}