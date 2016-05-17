#include "Font.h"

namespace Moo
{
	Font::Font()
	{
		_font = std::make_shared<Texture>();
		_letters['0'] = Moo::Vector2f(16, 0);
		_letters['1'] = Moo::Vector2f(17, 0);
		_letters['2'] = Moo::Vector2f(18, 0);
		_letters['3'] = Moo::Vector2f(19, 0);
		_letters['4'] = Moo::Vector2f(20, 0);
		_letters['5'] = Moo::Vector2f(21, 0);
		_letters['6'] = Moo::Vector2f(22, 0);
		_letters['7'] = Moo::Vector2f(23, 0);
		_letters['8'] = Moo::Vector2f(24, 0);
		_letters['9'] = Moo::Vector2f(25, 0);
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