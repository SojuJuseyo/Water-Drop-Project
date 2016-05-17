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

	}

	void	Text::setText(const std::string &text)
	{
		for (auto c : _text) {
			auto letter = std::make_shared<Sprite>(_size * 20.f, _size * 10.f, _x + (_size * 20.f), _y);
			letter->loadTexture(_font->getFont().get());
			_letters.push_back(letter);
		}
	}

	void	Text::draw(Window &window)
	{
		for (auto letter : _letters)
			window.draw(letter.get());
	}
}