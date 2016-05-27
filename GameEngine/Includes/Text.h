#pragma once

#include "Texture.h"
#include "SpriteRect.h"
#include "Sprite.h"
#include "Font.h"
#include "Window.h"

namespace Moo
{
	class Text
	{
	public:

		Text() {}
		Text(const std::string &text, float size, float x, float y, std::shared_ptr<Font>);
		~Text();
		void setText(const std::string &text);
		void draw();
		Vector2f getPosition();
		void setPosition(Vector2f);

	private:
		std::map<std::string, Moo::Vector2f> _spriteSheet;
		float	_size;
		Vector2f _pos;
		std::string _text;
		std::shared_ptr<Font> _font;
		std::vector<Sprite> _letters;
	};
}