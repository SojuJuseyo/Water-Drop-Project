#pragma once

#include <iostream>
#include <string>

class Tile
{

private:

	int	posX;
	int posY;

public:

	Tile();
	~Tile();

	// Setters and Getters
	void setPosX(int);
	int getPosX() const;

	void setPosY(int);
	int getPosY() const;
};