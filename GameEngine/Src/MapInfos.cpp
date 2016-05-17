#include "MapInfos.h"

MapInfos::MapInfos()
{

}

MapInfos::~MapInfos()
{

}

// Display all the map. Debug function
void MapInfos::displayMapInfos()
{
	std::cout << "Map Name : " << this->mapName << std::endl;
	std::cout << "Map Width : " << this->mapWidth << std::endl;
	std::cout << "Map Height : " << this->mapHeight << std::endl;
	std::cout << "Number of different sprites used : " << this->mapTileList.size() << std::endl;

	for (std::list<std::pair<std::string, std::list<Tile>>>::iterator it = this->mapTileList.begin(); it != this->mapTileList.end(); it++)
	{
		std::cout << "Sprite used : " << (*it).first << std::endl;
		std::cout << "Number of elements : " << (*it).second.size() << std::endl;

		std::list<Tile> tileList = (*it).second;
		for (std::list<Tile>::iterator it2 = tileList.begin(); it2 != tileList.end(); it2++)
		{
			std::cout << "Tile in [" << (*it2).getPosX() << ", " << (*it2).getPosY() << "]" << std::endl;
			TileProperties properties = (*it2).getProperties();
			std::cout << properties.getText() << std::endl;
			std::cout << properties.getSize() << std::endl;
			std::cout << (int)properties.getDirection() << std::endl;
		}
	}
}

std::list<Tile> MapInfos::getTilesFromSprite(std::string _sprite)
{
	for (std::list<std::pair<std::string, std::list<Tile>>>::iterator it = this->mapTileList.begin(); it != this->mapTileList.end(); it++)
	{
		if (_stricmp(_sprite.c_str(), (*it).first.c_str()) == 0)
			return ((*it).second);
	}
	return ((std::list<Tile>)NULL);
}

////////////////////////////////
// Setters and getters
////////////////////////////////

void MapInfos::setMapName(std::string _mapName)
{
	this->mapName = _mapName;
}

std::string MapInfos::getMapName() const
{
	return (this->mapName);
}

void MapInfos::setMapWidth(float _mapWidth)
{
	this->mapWidth = _mapWidth;
}

float MapInfos::getMapWidth() const
{
	return (this->mapWidth);
}

void MapInfos::setMapHeight(float _mapHeight)
{
	this->mapHeight = _mapHeight;
}

float MapInfos::getMapHeight() const
{
	return (this->mapHeight);
}

void MapInfos::setMapAudioFile(std::string _filePath)
{
	this->mapAudioFile = _filePath;
}

std::string MapInfos::getMapAudioFile() const
{
	return (this->mapAudioFile);
}

void MapInfos::setMapBackgroundFile(std::string _filePath)
{
	this->mapBackgroundFile = _filePath;
}

std::string MapInfos::getMapBackgroundFile() const
{
	return (this->mapBackgroundFile);
}

void MapInfos::setMapTileList(std::list< std::pair< std::string, std::list<Tile> > > _mapTileList)
{
	this->mapTileList = _mapTileList;
}

std::list < std::pair<std::string, std::list<Tile>> > MapInfos::getMapTileList() const
{
	return (this->mapTileList);
}

void MapInfos::setHeatZonesTileList(std::list<Tile> _mapHeatZonesList)
{
	this->mapHeatZonesList = _mapHeatZonesList;
}

std::list<Tile> MapInfos::getHeatZonesTileList() const
{
	return (this->mapHeatZonesList);
}

void MapInfos::setOtherTileList(std::list<Tile> _otherTileList)
{
	this->otherTileList = _otherTileList;
}

std::list<Tile> MapInfos::getOtherTileList() const
{
	return (this->otherTileList);
}