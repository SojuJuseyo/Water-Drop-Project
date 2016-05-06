#pragma once

#include <iostream>
#include <string>

class Tile
{

private:

	float	_posX;
	float	_posY;
	bool	_isHeatZone;
	bool	_isCollidable;

public:

	Tile();
	~Tile();

	// Setters and Getters
	void	setPosX(float);
	float	getPosX() const;

	void	setPosY(float);
	float	getPosY() const;

	void	setIsHeatZone(bool);
	bool	getIsHeatZone() const;

	void	setIsCollidable(bool);
	bool	getIsCollidable() const;
};