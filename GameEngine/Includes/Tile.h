#pragma once

#include <iostream>
#include <string>

class Tile
{

private:

	float	_posX;
	float	_posY;
	bool	_isHeatZone;

public:

	Tile();
	~Tile();

	// Setters and Getters
	void	setPosX(float);
	float	getPosX() const;

	void	setPosY(float);
	float	getPosY() const;

	void	setisHeatZone(bool);
	bool	getisHeatZone() const;
};