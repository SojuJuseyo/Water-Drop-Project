#include "Text.h"

namespace Moo
{
	Text::Text(float size, float x, float y, std::shared_ptr<Font> font)
	{
		_size = size;
		_font = font;
		_sprite = std::make_shared<Sprite>(_size * 20.f, _size * 10.f, x, y);
		_sprite2 = std::make_shared<Sprite>(_size * 20.f, _size * 10.f, x + (_size * 20.f), y);
		_sprite->loadTexture(_font->getFont().get());
		_sprite2->loadTexture(_font->getFont().get());
		_sprite->setRectFromSpriteSheet(Moo::Vector2f(0, 0), Moo::Vector2f(10.f, 20.f));
		_sprite2->setRectFromSpriteSheet(Moo::Vector2f(0, 0), Moo::Vector2f(10.f, 20.f));
	}

	Text::~Text()
	{

	}

	void	Text::setText(const std::string &text)
	{
		if (value > 0 && value < 99) {
			_sprite->setRectFromSpriteSheet(_font->getLetters().at((value / 10) + '0'), Moo::Vector2f(10.f, 20.f));
			_sprite2->setRectFromSpriteSheet(_font->getLetters().at((value % 10) + '0'), Moo::Vector2f(10.f, 20.f));
		}
	}

	Moo::Sprite	*Text::getSprite()
	{
		return _sprite.get();
	}
	Moo::Sprite	*Text::getSprite2()
	{
		return _sprite2.get();
	}
}