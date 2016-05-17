#include "Text.h"

namespace Moo
{
	Text::Text(const std::string &text, float size, float x, float y, Font font)
	{
		_size = size;
		_font = font;
		_x = x;
		_y = y;
		setText(text);
	}

	Text::~Text()
	{

	}

	void	Text::setText(const std::string &text)
	{
		_text.clear();
		int i = -1;
		for (auto c : text) {
			auto sprite = Moo::Sprite(_size * 10.f, _size * 20.f, _x + ((_size * 10.f) * ++i), _y);
			sprite.loadTexture(_font.getFont().get());
			sprite.setRectFromSpriteSheet(_font.getLetters().at(c), Moo::Vector2f(10.f, 20.f));
			_text.push_back(std::make_shared<Moo::Sprite>(sprite));
		}
	}

	void	Text::draw(Moo::Window &window)
	{
		for (auto letter : _text) {
			window.draw(letter.get());
		}
	}
}