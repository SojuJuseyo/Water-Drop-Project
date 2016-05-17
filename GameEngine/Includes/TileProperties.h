#pragma once

#include <iostream>
#include <string>
#include "Entity.h"

class TileProperties
{

private:
	
	std::string _text;
	int			_x2;
	int			_y2;
	int			_size;
	Direction	_orientation;
	bool		_isSet;

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

	void	setSize(int);
	int		getSize() const;

	void	setDirection(Direction);
	Direction getDirection() const;

	void	setIsSet(bool);
	bool	getIsSet() const;
};