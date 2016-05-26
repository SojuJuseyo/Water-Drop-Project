#include "Text.h"

namespace Moo
{
	Text::Text(const std::string &text, float size, float x, float y, std::shared_ptr<Font> font)
	{
		_size = size;
		_x = x;
		_y = y;
		_font = font;
		_text = text;
		setText(text);
	}

	Text::~Text()
	{
		_text.clear();
		_letters.clear();
	}

	void	Text::setText(const std::string &text)
	{
		_text.clear();
		_letters.clear();
		int i = 0;
		for (auto c : text) {
			auto sprite = Moo::Sprite(_size * 16.f, _size * 16.f, _x + ((_size * 16.f) * i++), _y);
			sprite.loadTexture(_font->getFont().get());
			sprite.setRectFromSpriteSheet(_font->getLetters().at(c), Moo::Vector2f(63.9f, 64.f));
			_letters.push_back(sprite);
		}
	}

	void	Text::draw(Window &window)
	{
		for (auto letter : _letters)
			window.draw(&letter);
	}
}