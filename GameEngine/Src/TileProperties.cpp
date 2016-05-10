#include "TileProperties.h"

TileProperties::TileProperties()
{

}

TileProperties::~TileProperties()
{

}

////////////////////////////////
// Setters and getters
////////////////////////////////

void			TileProperties::setText(std::string text)
{
	_text = text;
}

std::string		TileProperties::getText() const
{
	return (_text);
}

void			TileProperties::setX2(int x2)
{
	_x2 = x2;
}

int				TileProperties::getX2() const
{
	return (_x2);
}

void			TileProperties::setY2(int y2)
{
	_y2 = y2;
}

int				TileProperties::getY2() const
{
	return (_y2);
}