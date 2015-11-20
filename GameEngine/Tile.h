#pragma once

#include <iostream>
#include <string>

class Tile
{

private:

	float	posX;
	float	posY;

public:

	Tile();
	~Tile();

	// Setters and Getters
	void	setPosX(float);
	float	getPosX() const;

	void	setPosY(float);
	float	getPosY() const;
};