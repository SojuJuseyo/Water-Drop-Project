#pragma once

#include "Texture.h"
#include "SpriteRect.h"
#include "Sprite.h"
#include "Font.h"

namespace Moo
{
	class Text
	{
	public:
		Text(float size, float x, float y, std::shared_ptr<Font>);
		~Text();
		void setValue(int value);
		Moo::Sprite	*getSprite();
		Moo::Sprite *getSprite2();

	private:
		std::map<std::string, Moo::Vector2f> _spriteSheet;
		float	_size;
		std::shared_ptr<Font> _font;
		std::shared_ptr<Moo::Sprite> _sprite, _sprite2;
	};
}