#include "Text.h"


namespace Moo
{
	Text::Text(const std::string &text, float size, float x, float y, std::shared_ptr<Font> font)
	{
		_size = size;
		_pos.x = x;
		_pos.y = y;
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
		int i = 0;
		_letters.clear();
		for (auto c : text) {
			auto sprite = Moo::Sprite(_size * 16.f, _size * 16.f, _pos.x + ((_size * 16.f) * i++), _pos.y);
			sprite.loadTexture(_font->getFont().get());
			sprite.setRectFromSpriteSheet(_font->getLetters().at(c), Moo::Vector2f(63.9f, 64.f));
			_letters.push_back(sprite);
		}
		_text = text;
	}

	void	Text::draw()
	{
		for (auto letter : _letters)
			letter.draw();
	}

	Vector2f Text::getPosition()
	{
		return _pos;
	}

	void Text::setPosition(Vector2f pos)
	{
		_pos = pos;
		int i = 0;
		for (std::vector<Sprite>::iterator it = _letters.begin(); it != _letters.end(); it++) {
			(*it).setPosition(_pos.x + ((_size * 16.f) * i++), _pos.y);
		}
	}

}