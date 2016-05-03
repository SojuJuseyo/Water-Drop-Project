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

void Tile::setPosX(float posX)
{
	this->_posX = posX;
}

float Tile::getPosX() const
{
	return (this->_posX);
}

void Tile::setPosY(float posY)
{
	this->_posY = posY;
}

float Tile::getPosY() const
{
	return (this->_posY);
}

void Tile::setisHeatZone(bool isHeatZone)
{
	this->_isHeatZone = isHeatZone;
}

bool Tile::getisHeatZone() const
{
	return (this->_isHeatZone);
}