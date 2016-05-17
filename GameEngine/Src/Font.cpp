#include "Font.h"

namespace Moo
{
	Font::Font()
	{
		_font = std::make_shared<Texture>();
		int i = -1;
		for (char c : " !²#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[²]^_`abcdefghijklmnopqrstuvwxyz{|}~") {
			_letters[c] = Moo::Vector2f(++i, 0);
		}

	}

	Font::~Font()
	{
		
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