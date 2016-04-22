#include "SpriteRect.h"

namespace Moo
{
	SpriteRect::SpriteRect()
	{}

	SpriteRect::SpriteRect(
		float widthSprite,
		float heightSprite,
		float widthTexture,
		float heightTexture,
		float widthWholeTexture,
		float heightWholeTexture)
	{
		_widthSprite = widthSprite;
		_heightSprite = heightSprite;
		_widthTexture = widthTexture;
		_heightTexture = heightTexture;
		_widthWholeTexture = widthWholeTexture;
		_heightWholeTexture = heightWholeTexture;
		_offsetX = widthTexture / widthWholeTexture;
		_offsetY = heightTexture / heightWholeTexture;
		_vertexTab = nullptr;
	}

	SpriteRect::~SpriteRect()
	{
		if (_vertexTab != nullptr)
			delete _vertexTab;
	}

	VERTEX *SpriteRect::makeVertexTab(int x, int y) // Créer un tableau de vertex pour la texture correspondant à l'emplacement du sprite désiré sur la texture avec x et y
	{
		if (_vertexTab != nullptr)
			delete _vertexTab;
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