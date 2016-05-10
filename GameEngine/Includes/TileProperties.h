#pragma once

#include <iostream>
#include <string>

class TileProperties
{

private:

	std::string _text;
	int			_x2;
	int			_y2;

public:

	TileProperties();
	~TileProperties();

	// Setters and Getters
	void		setText(std::string);
	std::string	getText() const;

	void	setX2(int);
	int		getX2() const;

	void	setY2(int);
	int		getY2() const;
};