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

void Tile::setIsHeatZone(bool isHeatZone)
{
	this->_isHeatZone = isHeatZone;
}

bool Tile::getIsHeatZone() const
{
	return (this->_isHeatZone);
}

void Tile::setIsCollidable(bool isCollidable)
{
	this->_isCollidable = isCollidable;
}

bool Tile::getIsCollidable() const
{
	return (this->_isCollidable);
}