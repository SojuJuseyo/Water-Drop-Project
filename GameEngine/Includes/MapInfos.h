#pragma once

#include "Tile.h"

#include <list>
#include <utility>

// Map related field names & attributes
#define MAP_NAME_ATTRIBUTE				"name"
#define MAP_SIZE_ATTRIBUTE				"size"
#define MAP_BLOCK_TILE_LIST_ATTRIBUTE	"blockTileList"
#define MAP_PLAYER_TILE_LIST_ATTRIBUTE  "playerTileList"
#define MAP_ENEMY_TILE_LIST_ATTRIBUTE	"enemyTileList"
#define MAP_HEATZONE_LIST_ATTRIBUTE		"heatZonesList"
#define MAP_OTHER_TILE_LIST				"otherTileList"
#define MAP_AUDIO_ATTRIBUTE				"audio"
#define MAP_BACKGROUND_ATTRIBUTE		"background"
#define MAP_COORD_X						"coordx"
#define MAP_COORD_Y						"coordy"
#define MAP_COLLIDABLE_TILE				"collidable"
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
	std::list< std::pair< std::string, std::list<Tile> > > blockTileList;
	std::list< std::pair< std::string, std::list<Tile> > > playerTileList;
	std::list< std::pair< std::string, std::list<Tile> > > enemyTileList;
	std::list<Tile>	mapHeatZonesList;
	std::list<Tile> otherTileList;
	std::list<Tile>	isNotCollidable;

public:

	MapInfos();
	~MapInfos();

	void displayMapInfos();

	std::list<Tile> getTilesFromSprite(std::string);
	std::list<Tile> getPlayerTilesFromSprite(std::string);
	std::list<Tile> getEnemyTilesFromSprite(std::string);

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

	void setBlockTileList(std::list<std::pair<std::string, std::list<Tile>>>);
	std::list<std::pair<std::string, std::list<Tile>>> getBlockTileList() const;

	void setPlayerTileList(std::list<std::pair<std::string, std::list<Tile>>>);
	std::list<std::pair<std::string, std::list<Tile>>> getPlayerTileList() const;

	void setEnemyTileList(std::list<std::pair<std::string, std::list<Tile>>>);
	std::list<std::pair<std::string, std::list<Tile>>> getEnemyTileList() const;

	void setHeatZonesTileList(std::list<Tile>);
	std::list<Tile> getHeatZonesTileList() const;

	void setOtherTileList(std::list<Tile>);
	std::list<Tile> getOtherTileList() const;
};