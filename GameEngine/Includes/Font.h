#pragma once

#include "Texture.h"
#include "SpriteRect.h"
#include "Sprite.h"

#define FONTS_PATH "Ressources/Fonts/"

namespace Moo
{
	class Font
	{
	public:
		Font();
		~Font();
		std::map<char, Moo::Vector2f> getLetters();
		void	loadFromFile(const std::string&);
		std::shared_ptr<Moo::Texture> getFont();
	private:
		std::map<char, Moo::Vector2f> _letters;
		std::shared_ptr<Moo::Texture> _font;
	};
}