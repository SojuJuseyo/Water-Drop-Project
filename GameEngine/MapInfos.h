#pragma once

#include "Tile.h"

#include <list>
#include <utility>

class MapInfos
{

private:

	// Informations of the map
	std::string mapName;
	float mapWidth;
	float mapHeight;
	std::list<std::pair<std::string,std::list<Tile *>>> mapTileList;

public:

	MapInfos();
	~MapInfos();

	void displayMapInfos();

	std::list<Tile *> getTilesFromColor(std::string);

	// Setters and Getters
	void setMapName(std::string);
	std::string getMapName() const;

	void setMapWidth(float);
	float getMapWidth() const;

	void setMapHeight(float);
	float getMapHeight() const;

	void setMapTileList(std::list<std::pair<std::string, std::list<Tile *>>>);
	std::list<std::pair<std::string, std::list<Tile *>>> getMapTileList() const;

};