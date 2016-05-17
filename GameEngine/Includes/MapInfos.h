#pragma once

#include "Tile.h"

#include <list>
#include <utility>

// Map related field names & attributes
#define MAP_NAME_ATTRIBUTE				"name"
#define MAP_SIZE_ATTRIBUTE				"size"
#define MAP_TILE_LIST_ATTRIBUTE			"tileList"
#define MAP_HEATZONE_LIST_ATTRIBUTE		"heatZonesList"
#define MAP_AUDIO_ATTRIBUTE				"audio"
#define MAP_BACKGROUND_ATTRIBUTE		"background"
#define MAP_COORD_X						"coordx"
#define MAP_COORD_Y						"coordy"
#define MAP_COLLIDABLE_TILE				"collidable"
#define MAP_OTHER_TILE_LIST				"otherTileList"
#define MAP_PROPERTIES					"properties"

class MapInfos
{

private:

	// Informations of the map
	std::string	mapName;
	float mapWidth;
	float mapHeight;
	std::string mapAudioFile;
	std::string mapBackgroundFile;
	// std::string -> "0" or "1" or "2" ... 0 being the first sprite of the spritesheet, 1 the second etc ...
	std::list< std::pair< std::string,std::list<Tile> > > mapTileList;
	std::list<Tile>	mapHeatZonesList;
	std::list<Tile> otherTileList;
	std::list<Tile>	isNotCollidable;

public:

	MapInfos();
	~MapInfos();

	void displayMapInfos();

	std::list<Tile> getTilesFromSprite(std::string);

	// Setters and Getters
	void setMapName(std::string);
	std::string getMapName() const;

	void setMapWidth(float);
	float getMapWidth() const;

	void setMapHeight(float);
	float getMapHeight() const;

	void setMapAudioFile(std::string);
	std::string getMapAudioFile() const;

	void setMapBackgroundFile(std::string);
	std::string getMapBackgroundFile() const;

	void setMapTileList(std::list<std::pair<std::string, std::list<Tile>>>);
	std::list<std::pair<std::string, std::list<Tile>>> getMapTileList() const;

	void setHeatZonesTileList(std::list<Tile>);
	std::list<Tile> getHeatZonesTileList() const;

	void setOtherTileList(std::list<Tile>);
	std::list<Tile> getOtherTileList() const;
};