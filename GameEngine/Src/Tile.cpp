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

void Tile::setPosX(float _posX)
{
	this->posX = _posX;
}

float Tile::getPosX() const
{
	return (this->posX);
}

void Tile::setPosY(float _posY)
{
	this->posY = _posY;
}

float Tile::getPosY() const
{
	return (this->posY);
}