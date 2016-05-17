#pragma once

#include "Texture.h"
#include "Window.h"
#include "SpriteRect.h"
#include "Sprite.h"
#include "Font.h"

namespace Moo
{
	class Text
	{
	public:
		Text() {}
		Text(const std::string &text, float size, float x, float y, Font);
		~Text();
		void setText(const std::string &text);
		void draw(Moo::Window& window);

	private:
		std::map<std::string, Moo::Vector2f> _spriteSheet;
		float	_size, _x, _y;
		Font _font;
		std::vector<std::shared_ptr<Moo::Sprite>> _text;
	};
}