#include "Tile.h"

Tile::Tile()
{

}

Tile::~Tile()
{

}

////////////////////////////////
// Setters and getters
////////////////////////////////

void Tile::setPosX(int _posX)
{
	this->posX = _posX;
}

int Tile::getPosX() const
{
	return (this->posX);
}

void Tile::setPosY(int _posY)
{
	this->posY = _posY;
}

int Tile::getPosY() const
{
	return (this->posY);
}