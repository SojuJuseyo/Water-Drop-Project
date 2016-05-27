#include "Font.h"

namespace Moo
{
	Font::Font()
	{
		_font = std::make_shared<Texture>();
		float i = 0.f;
		for (char c : "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvw.yz ") {
				_letters[c] = Moo::Vector2f(i++, 0.f);
		}
	}

	Font::~Font()
	{
		_font.reset();
	}

	std::map<char, Moo::Vector2f> Font::getLetters()
	{
		return _letters;
	}

	void	Font::loadFromFile(const std::string &filename)
	{
		_font->loadFromFile(FONTS_PATH + std::string(filename));
	}

	std::shared_ptr<Moo::Texture> Font::getFont()
	{
		return _font;
	}
}